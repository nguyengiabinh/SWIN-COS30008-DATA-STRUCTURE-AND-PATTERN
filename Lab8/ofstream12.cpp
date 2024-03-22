#include"ofstream12.h"
using namespace std;
void ofstream12::init() {
	for (int i = 0; i < fBufferSize; i++) {
		fBuffer[i] = 0;
	}
	fByteIndex = 0;
	fBitIndex = 7;
}
void ofstream12::completeWriteBit() {
	if (fBitIndex < 0) {
		fByteIndex++;
		fBitIndex = 7;
	}
	if (fByteIndex == fBufferSize) {
		flush();
	}

}
ofstream12::ofstream12(const char* aFileName, size_t aBufferSize) {
	fBufferSize = aBufferSize;
	fBuffer = new byte[fBufferSize];
	init();
	open(aFileName);

}
ofstream12::~ofstream12() {
	delete[] fBuffer;
}
void ofstream12::flush() {
	if (isOpen() && fByteIndex > 0) {
		fOStream.write(reinterpret_cast<const char*>(fBuffer), fByteIndex);
		fByteIndex = 0;
	}
}
void ofstream12::writeBit0() {
	fBuffer[fBitIndex] += 0;
	fBitIndex--;
	completeWriteBit();
}
void ofstream12::writeBit1() {
	fBuffer[fByteIndex] += (1 << fBitIndex);
	fBitIndex--;
	completeWriteBit();

}
void ofstream12::open(const char* aFileName) {
	close();
	fOStream.open(aFileName, std::ios::binary);
}
void ofstream12::close() {
	flush();
	fOStream.close();
}
bool ofstream12::good() const {
	return fOStream.good();
}
bool ofstream12::isOpen() const {
	if (!fOStream.is_open()) {
		return false;
	}
	return true;
}
ofstream12& ofstream12::operator<<(size_t aValue) {
	for (int i = 0; i < 12; i++) {
		if (aValue & 1) {
			writeBit1();
		}
		else {
			writeBit0();
		}
		aValue /= 2;
	}
	return (*this);
}
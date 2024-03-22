#include "iVigenereStream.h"

iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName) : fIStream(std::ifstream()), fCipherProvider(Vigenere(aKeyword)), fCipher(std::move(aCipher))
{
	open(aFileName);
}

iVigenereStream::~iVigenereStream()
{
	close();
}

void iVigenereStream::open(const char* aFileName)
{
	fIStream.open(aFileName);
}

void iVigenereStream::close()
{
	fIStream.close();
}

void iVigenereStream::reset()
{
	fCipherProvider.reset();
	seekstart();
}

bool iVigenereStream::good() const
{
	return fIStream.good();
}

bool iVigenereStream::is_open() const
{
	return fIStream.is_open();
}

bool iVigenereStream::eof() const
{
	return fIStream.eof();
}

iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
	char lcipheredChar = static_cast<char>(fIStream.get());
	aCharacter = fCipher(fCipherProvider, lcipheredChar);
	return *this;
}
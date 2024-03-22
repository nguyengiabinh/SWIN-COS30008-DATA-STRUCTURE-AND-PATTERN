#include "KeyProvider.h"

KeyProvider::KeyProvider(const std::string& aKeyword) : fKeyword(new char[aKeyword.length()]), fSize(aKeyword.length()), fIndex(0)
{
	initialize(aKeyword);
}

KeyProvider::~KeyProvider()
{
	delete[] fKeyword;
}

void KeyProvider::initialize(const std::string& aKeyword)
{
	delete[] fKeyword;
	fSize = aKeyword.size();
	fKeyword = new char[fSize];
	for (size_t i = 0; i < fSize; i++)
	{
		int lasciiValue = static_cast<int>(aKeyword[i]);
		if (lasciiValue >= 97 && lasciiValue <= 122) {
			lasciiValue -= 32;
		}
		fKeyword[i] = static_cast<char>(lasciiValue);
	}
	fIndex = 0;
}


char KeyProvider::operator*() const
{
	return fKeyword[fIndex];
}

KeyProvider& KeyProvider::operator<<(char aKeyCharacter) {
	fKeyword[fIndex] = static_cast<char>(toupper(aKeyCharacter));
	fIndex = (fIndex + 1 == fSize) ? 0 : fIndex + 1;
	return *this;
}
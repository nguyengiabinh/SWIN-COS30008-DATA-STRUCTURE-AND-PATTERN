#include "Vigenere.h"

void Vigenere::initializeTable()
{
	for (char row = 0; row < CHARACTERS; row++)
	{
		char lChar = 'B' + row;
		for (char column = 0; column < CHARACTERS; column++)
		{
			if (lChar > 'Z')
				lChar = 'A';
			fMappingTable[row][column] = lChar++;
		}
	}
}

Vigenere::Vigenere(const std::string& aKeyword): fKeyword(aKeyword), fKeywordProvider(KeyProvider(aKeyword)) 
{
	initializeTable();
}

std::string Vigenere::getCurrentKeyword()
{
	std::string lcurrentKey;

	for (size_t i = 0; i < fKeyword.length(); i++)
	{
		lcurrentKey = lcurrentKey + *fKeywordProvider;
		fKeywordProvider << *fKeywordProvider;
	}
	return lcurrentKey;
}

void Vigenere::reset()
{
	fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter) {
	if (!isalpha(aCharacter)) {
		return aCharacter; 
	}

	char lupperCase = toupper(aCharacter);
	char lencoded = fMappingTable[*fKeywordProvider - 'A'][lupperCase - 'A'];
	fKeywordProvider << aCharacter;
	return (islower(aCharacter)) ? tolower(lencoded) : lencoded;
}

char Vigenere::decode(char aCharacter) {
	if (!isalpha(aCharacter)) {
		return aCharacter; 
	}

	char lupperCase = toupper(aCharacter);
	for (size_t i = 0; i < CHARACTERS; i++) {
		if (fMappingTable[*fKeywordProvider - 'A'][i] == lupperCase) {
			char ldecoded = i + 'A';
			fKeywordProvider << ldecoded;
			return (islower(aCharacter)) ? tolower(ldecoded) : ldecoded;
		}
	}
	return aCharacter;
}
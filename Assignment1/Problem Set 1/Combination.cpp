#include "Combination.h"

Combination::Combination(size_t aN, size_t aK): fN(aN),fK(aK){
}

size_t Combination::getN() const {
	return fN;
}

size_t Combination::getK() const {
	return fK;
}

unsigned long long Combination::operator()() const {
	if (fK > fN) {
		return 0;
	}

	unsigned long long lResult = 1;
	for (size_t i = 0; i < fK; i++) {
		//float would work here too but i can see that result is in long long so i use double to have a more accurate decimal 
		//which does not matter in this case but just to be save.
		lResult *= static_cast<double>(fN - i) / (i + 1);
	}

	return lResult;
}
#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial() : fDegree(0) {
	for (size_t i = 0; i <= MAX_DEGREE; i++) {
		fCoeffs[i] = 0.0;
	}
}

bool Polynomial::operator==(const Polynomial& aRHS) const {
	bool Result = fDegree == aRHS.fDegree;

	for (size_t i = 0; Result && i <= fDegree; i++) {
		if (fCoeffs[i] != aRHS.fCoeffs[i]) {
			Result = false;
		}
	}

	return Result;
}

Polynomial Polynomial::operator*(const Polynomial& aRHS) const {
	Polynomial Result;

	Result.fDegree = fDegree + aRHS.fDegree;
	for (size_t i = 0; i <= fDegree; i++) {
		for (size_t j = 0; j <= aRHS.fDegree; j++) {
			Result.fCoeffs[i + j] += fCoeffs[i] * aRHS.fCoeffs[j];
		}
	}

	return Result;
}

ostream& operator<<(std::ostream& aOStream, const Polynomial& aObject) {
	bool lMustPrintPlus = false;

	for (int i = static_cast<int>(aObject.fDegree); i >= 0; i--) {
		if (aObject.fCoeffs[i] != 0) {
			if (lMustPrintPlus) {
				aOStream << " + ";
			}
			else {
				lMustPrintPlus = true;
			}

			aOStream << aObject.fCoeffs[i] << "x^" << i;
		}
	}

	return aOStream;
}

istream& operator>> (std::istream& aIStream, Polynomial& aObject) {
	size_t lDegree;

	aIStream >> lDegree;

	aObject.fDegree = lDegree <= MAX_POLYNOMIAL ? lDegree : MAX_POLYNOMIAL;

	for (int i = static_cast<int>(aObject.fDegree); i >= 0; i--) {
		aIStream >> aObject.fCoeffs[i];
	}

	return aIStream;
}

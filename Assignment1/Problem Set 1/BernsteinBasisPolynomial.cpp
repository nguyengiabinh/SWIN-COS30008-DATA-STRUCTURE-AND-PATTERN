#include "BernsteinBasisPolynomial.h"
#include "Combination.h"
#include <cmath> 

BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV, unsigned int aN) : fFactor(aN, aV) {
	
}

//double BernsteinBasisPolynomial::operator()(double aX) const {
//	double lResult;
//	lResult = fFactor() * pow(aX, fFactor.getK()) * pow((1 - aX), (fFactor.getN() - fFactor.getK()));
//	return lResult;
//}

//i was going with the one liner but after reading the Preliminaries in the pdf again, the requirement seems to emphasize on the for-loop 
//so i adapt the code and it return the same result as the example in the pdf

double BernsteinBasisPolynomial::operator() (double aX) const {
	double lResult = fFactor();
	for (size_t i = 0; i < fFactor.getK(); i++) {
		lResult *= pow(aX, 1.0); 
	}

	for (size_t i = 0; i < fFactor.getN() - fFactor.getK(); i++) {
		lResult *= pow(1 - aX, 1.0);
	}

	return lResult;
}
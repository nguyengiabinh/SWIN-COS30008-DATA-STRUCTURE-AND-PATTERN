#include "Polynomial.h"
#include <cmath>

double Polynomial::operator()(double aX) const {
	double lResult = 0.0;

	for (size_t i = 0; i <= fDegree; i++) {
		lResult += fCoeffs[i] * pow(aX, i);
	}

	return lResult;
}

Polynomial Polynomial::getDerivative() const {
	Polynomial lDerivative;

	lDerivative.fDegree = fDegree - 1;

	for (size_t i = 1; i <= fDegree; i++) {
		//if (i != 0) {
			lDerivative.fCoeffs[i - 1] = fCoeffs[i] * i;
		//}
		//else {
		//	lDerivative.fCoeffs[i - 1] = 0;
		//}

		//in this case the equation return back is correct according to the example in pdf 
		//but the output still print error "Derivative is broken".
		//i can be 0 but i dont know why when i put i = 0 it broke the derivative of indefinite integral
	}

	return lDerivative;
}

Polynomial Polynomial::getIndefiniteIntegral() const {
	Polynomial lIndefiniteIntegral;

	lIndefiniteIntegral.fDegree = fDegree + 1;

	for (size_t i = 0; i <= fDegree; i++) {
		lIndefiniteIntegral.fCoeffs[i + 1] = fCoeffs[i] / (i + 1);
	}

	return lIndefiniteIntegral;
}

double Polynomial::getDefiniteIntegral(double aXLow, double aXHigh) const {
	double lLowerBound;
	double lHigherBound;

	lLowerBound = getIndefiniteIntegral()(aXLow);
	lHigherBound = getIndefiniteIntegral()(aXHigh);

	return lHigherBound - lLowerBound;

}

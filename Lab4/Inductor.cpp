#define _USE_MATH_DEFINES

#include "Inductor.h"
#include <cmath>

using namespace std;

// auxiliary methods
// aValue < 1.0
bool Inductor::mustScale(double aValue) const {
	return aValue < 1.0;
}

// 1000.0
const double Inductor::getMultiplier() const {
	return 1000.0;
}

// "H"
const string Inductor::getMajorUnit() const {
	return "H";
}

// minor units: "Hmunp", the first letter means "no major unit"
const string Inductor::getMinorUnits() const {
	return "Hmunp";
}

// constructor with a default value
Inductor::Inductor(double aBaseValue) : ResistorBase(aBaseValue) {

}

// returns (frequency-dependent) passive resistance value
double Inductor::getReactance(double aFrequency) const {
	return (2 * M_PI * aFrequency * getBaseValue());
}
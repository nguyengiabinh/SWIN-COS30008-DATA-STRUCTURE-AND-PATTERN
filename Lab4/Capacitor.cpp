#define _USE_MATH_DEFINES

#include "Capacitor.h"
#include <cmath>

using namespace std;

// auxiliary methods
// aValue < 1.0
bool Capacitor::mustScale(double aValue) const {
    return aValue < 1.0;
}

// 1000.0
const double Capacitor::getMultiplier() const {
    return 1000.0;
}

// "F"
const string Capacitor::getMajorUnit() const {
    return "F";
}
// minor units: "Fmunp", the first letter means "no major unit"
const string Capacitor::getMinorUnits() const {
    return "Fmunp";
}

// constructor with a default value
Capacitor::Capacitor(double aBaseValue) : ResistorBase(aBaseValue) {

}

// returns (frequency-dependent) passive resistance value
double Capacitor::getReactance(double aFrequency) const {
    return 1.0 / (2.0 * M_PI * aFrequency * getBaseValue());
}
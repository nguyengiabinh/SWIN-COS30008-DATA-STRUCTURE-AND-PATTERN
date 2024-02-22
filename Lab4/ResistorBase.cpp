
// COS30008, Tutorial 4, 2022

#include "ResistorBase.h"

#include <stdexcept>

using namespace std;

void ResistorBase::normalize( double& aNormalizedValue, string& aUnit ) const
{
    aNormalizedValue = getBaseValue();
    string lPrefixes = getMinorUnits();
    
    for ( size_t i = 0; i < lPrefixes.size(); i++ )
    {
        // stop scaling at maximum unit
        if ( mustScale( aNormalizedValue ) && (i < lPrefixes.size() - 1) )
        {
            aNormalizedValue *= getMultiplier();
        }
        else
        {
            if ( i > 0 )
            {
                aUnit += lPrefixes[i];
            }
            aUnit += getMajorUnit();
            break;
        }
    }
}

void ResistorBase::flatten( const double& aRawValue, const string& aRawUnit )
{
    string lMajorUnit = getMajorUnit();
    string lMinorUnits = getMinorUnits();

    // error handling
    // test basic features (raw unit too long and not containing major unit)
    if ( (aRawUnit.size() > lMajorUnit.size() + 1) ||
         (aRawUnit.find( getMajorUnit() ) == string::npos) )
    {
        throw invalid_argument( "Invalid unit specification" );
    }

    // test scale features, aRawUnit[0] must be contained in minor units
    if ( (aRawUnit.size() == lMajorUnit.size() + 1) &&
         lMinorUnits.find( aRawUnit[0] ) == string::npos )
    {
        throw invalid_argument( "Invalid unit scale specification" );
    }

    // adjust base value
    double lMultiplier = 1.0;
    
    size_t i = lMinorUnits.find( aRawUnit[0] );
    double lRawValue = aRawValue;

    // scale raw value first
    for ( ; i > 0 ; i-- )
    {
        if ( mustScale( lRawValue ) )
        {
            lRawValue /= getMultiplier();
        }
        else
        {
            break;
        }
    }

    // adjust multiplier
    for ( ; i > 0; i-- )
    {
        lMultiplier *= 1.0/getMultiplier();
    }

    setBaseValue( lRawValue * lMultiplier );
}

void ResistorBase::setBaseValue(double aBaseValue) {
    fBaseValue = aBaseValue;
}
double ResistorBase::getBaseValue() const {
    return fBaseValue;
}
double ResistorBase::getPotentialAt(double aCurrent, double aFrequency) const {
    double aVoltage = 1;
    if (aFrequency == 0) {
        aVoltage = getBaseValue() * aCurrent;
    }
    else {
        aVoltage = getReactance(aFrequency) * aCurrent;
    }
    return aVoltage;
}
double ResistorBase::getCurrentAt(double aVoltage, double aFrequency) const {
    double current = 1;
    if (aFrequency == 0) {
        current = aVoltage / getBaseValue();
    }
    else {
        current = aVoltage / getReactance(aFrequency);
    }
    return current;
}
std::istream& operator>>(std::istream& aIStream, ResistorBase& aObject) {
    double rawUnit;
    string rawValue;
    aIStream >> rawUnit >> rawValue;
    aObject.flatten(rawUnit, rawValue);
    return aIStream;
}
std::ostream& operator<<(std::ostream& aOStream, const ResistorBase& aObject) {
    double aUnit;
    string normal;
    aObject.normalize(aUnit, normal);
    aOStream << aUnit << " " << normal;
    return aOStream;
}

#include "IntVector.h"

#include <stdexcept>
#include <algorithm>

using namespace std;

IntVector::IntVector(const int aArrayOfIntegers[], size_t aNumberOfElements)
{
    fNumberOfElements = aNumberOfElements;
    fElements = new int[fNumberOfElements];

    for (size_t i = 0; i < fNumberOfElements; i++)
    {
        fElements[i] = aArrayOfIntegers[i];
    }
}

const int IntVector::get(size_t aIndex) const
{
    return (*this)[aIndex];
}

const int IntVector::operator[](size_t aIndex) const
{
    if (aIndex < fNumberOfElements)
    {
        return fElements[aIndex];
    }

    throw out_of_range("Illegal vector index");
}

std::ostream& operator<<(std::ostream & aOStream, const IntVector & aObject) {
        for (int i = 0; i < aObject.fNumberOfElements; i++) {
            aOStream << aObject.fElements[i] << " ";
        }
        return aOStream;
}

void IntVector::swap(size_t aSourceIndex, size_t aTargetIndex)
{
    if (aSourceIndex < fNumberOfElements &&
        aTargetIndex < fNumberOfElements)
    {
        std::swap(fElements[aSourceIndex], fElements[aTargetIndex]);
    }
    else
    {
        throw out_of_range("Illegal vector indices");
    }
}
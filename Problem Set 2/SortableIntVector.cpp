#include "SortableIntVector.h"

using namespace std;

SortableIntVector::SortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) : IntVector(aArrayOfIntegers, aNumberOfElements)
{
}

void SortableIntVector::sort(Comparable aOrderFunction)
{
    size_t lArraylength = size();
    for (size_t i = 0; i < lArraylength; i++)
    {
        for (size_t j = 0; j < lArraylength - i - 1; j++)
        {
            if (aOrderFunction((*this)[j + 1], (*this)[j]))
            {
                swap(j, j + 1);
            }
        }
    }
}

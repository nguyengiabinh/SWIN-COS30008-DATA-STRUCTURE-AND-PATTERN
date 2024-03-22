#include"ShakerSortableIntVector.h"

using namespace std;

ShakerSortableIntVector::ShakerSortableIntVector(const int aArrayOfIntegers[], size_t aNumberOfElements) : SortableIntVector(aArrayOfIntegers, aNumberOfElements) 
{
}

void ShakerSortableIntVector::sort(Comparable aOrderFunction)
{
    size_t lLeft = 0;
    size_t lRight = size() - 1;

    while (lLeft < lRight)
    {
        for (size_t i = lLeft; i < lRight; i++)
        {
            if (!aOrderFunction(get(i), get(i + 1)))
            {
                swap(i, i + 1);
            }
        }

        lRight--;

        for (size_t i = lRight; i > lLeft; i--)
        {
            if (!aOrderFunction(get(i - 1), get(i)))
            {
                swap(i - 1, i);
            }
        }

        lLeft++;
    }
}

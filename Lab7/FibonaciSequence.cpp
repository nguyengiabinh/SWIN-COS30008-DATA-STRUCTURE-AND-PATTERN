#include "FibonacciSequence.h"
#include "FibonacciSequenceIterator.h"

#include <stdexcept>

using namespace std;

FibonacciSequence::FibonacciSequence(uint64_t aLimit)
{
    fPrevious = 0;
    fCurrent = 1;
    fPosition = 1;
    fLimit = aLimit;
}

const uint64_t& FibonacciSequence::current() const
{
    return fCurrent;
}

void FibonacciSequence::advance()
{
    if (fLimit == 0 || fPosition <= fLimit)
    {
        uint64_t lNext = fCurrent + fPrevious;
        fPrevious = fCurrent;
        fCurrent = lNext;
        fPosition++;
    }
    else
    {
        throw out_of_range("sequence limit exceeded");
    }
}

const uint64_t& FibonacciSequence::getLimit() const
{
    return fLimit;
}

void FibonacciSequence::reset()
{
    fPrevious = 0;
    fCurrent = 1;
    fPosition = 1;
}

FibonacciSequenceIterator FibonacciSequence::begin() const
{
    FibonacciSequenceIterator Result(*this);

    return Result.begin();
}

FibonacciSequenceIterator FibonacciSequence::end() const
{
    FibonacciSequenceIterator Result(*this);

    return Result.end();
}
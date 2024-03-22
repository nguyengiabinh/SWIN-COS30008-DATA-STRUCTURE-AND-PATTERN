#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) : fIStream(aIStream), fCurrentChar(0), fEOF(aIStream.eof())
{
    if (!fEOF)
    {
        fIStream >> fCurrentChar;
    }
}

char VigenereForwardIterator::operator*() const
{
    return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++()
{

}


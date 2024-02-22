#include "Polygon.h"

float Polygon::getSignedArea() const {
	float lResult = 0.0;
    for (size_t i = 0; i < fNumberOfVertices; i++)
    {
        size_t lj = (i + 1) % fNumberOfVertices;
        lResult += (fVertices[i].getX() * fVertices[lj].getY() - fVertices[i].getY() * fVertices[lj].getX());
    }
    lResult *= 0.5;
    return lResult;
}
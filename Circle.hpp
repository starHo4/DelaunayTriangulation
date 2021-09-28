#ifndef __CircumscribedCircle__
#define __CircumscribedCircle__

#include "Header.hpp"

class Circle
{
private:
public:
    Circle();

    double radius;
    PVector center;

    // Calculate radius and center of circumscribed circle.
    void CalcCircle(Triangle &tri);
};

#endif
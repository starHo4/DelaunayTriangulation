#ifndef __CircumscribedCircle__
#define __CircumscribedCircle__

#include "Header.hpp"

class Circle
{
private:
public:
    Circle();
    Circle(Triangle &tri);

    double radius;
    PVector center;

    // Calculate radius and center of circumscribed circle.
    void CalcCircle(Triangle &tri);
};

#endif
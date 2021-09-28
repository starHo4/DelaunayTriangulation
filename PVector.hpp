#ifndef __PVector__
#define __PVector__

#include <cmath>

struct PVector
{
    double x, y;
    bool operator==(const PVector &v) const
    {
        return (x == v.x && y == v.y);
    }
    bool operator!=(const PVector &v) const
    {
        return (x != v.x || y != v.y);
    }
};

PVector Add(PVector u, PVector v);

PVector Diff(PVector u, PVector v);

PVector Mult(PVector u, double a);

double Dot(PVector u, PVector v);

double Norm(PVector u);

PVector Normalize(PVector u);

double Dist(PVector u, PVector v);

PVector NullVector();

PVector NewVec(double x, double y);

bool isSame(PVector v1, PVector v2);

#endif
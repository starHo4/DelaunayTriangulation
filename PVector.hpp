#ifndef __PVector__
#define __PVector__

#include <cmath>

struct PVector
{
    double x, y;

    // Constructors
    PVector() {}
    PVector(double _x, double _y)
    {
        x = _x;
        y = _y;
    }

    // whether or not this vector is another vector.
    bool operator==(const PVector &v) const
    {
        return (x == v.x && y == v.y);
    }
    bool operator!=(const PVector &v) const
    {
        return (x != v.x || y != v.y);
    }
    // Instead of Add function, operator '+'.
    PVector operator+(const PVector &v) const
    {
        double _x = x + v.x;
        double _y = y + v.y;
        return PVector(_x, _y);
    }
    // Instead of Diff function, operator '-'.
    PVector operator-(const PVector &v) const
    {
        double _x = x - v.x;
        double _y = y - v.y;
        return PVector(_x, _y);
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
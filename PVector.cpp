#include "PVector.hpp"

PVector Add(PVector u, PVector v)
{
    PVector w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    return w;
}

PVector Diff(PVector u, PVector v)
{
    PVector w;
    w.x = u.x - v.x;
    w.y = u.y - v.y;
    return w;
}

PVector Mult(PVector u, double a)
{
    PVector w;
    w.x = u.x * a;
    w.y = u.y * a;
    return w;
}

double Dot(PVector u, PVector v)
{
    double a = u.x * v.x + u.y * v.y;
    return a;
}

double Norm(PVector u)
{
    return sqrt(Dot(u, u));
}

PVector Normalize(PVector u)
{
    double norm = Norm(u);
    PVector v;
    if (norm == 0)
    {
        v.x = 0;
        v.y = 0;
        return v;
    }
    v.x = u.x / norm;
    v.y = u.y / norm;
    return v;
}

double Dist(PVector u, PVector v)
{
    PVector w = Diff(u, v);
    return Norm(w);
}

PVector NullVector()
{
    PVector w;
    w.x = 0;
    w.y = 0;
    return w;
}

PVector NewVec(double x, double y)
{
    PVector w;
    w.x = x;
    w.y = y;
    return w;
}

bool isSame(PVector v1, PVector v2)
{
    if (v1.x == v2.x && v1.y == v2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
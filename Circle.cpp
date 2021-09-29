#include "Circle.hpp"

Circle::Circle()
{
    radius = 0;
    center = NewVec(0, 0);
}

Circle::Circle(Triangle &tri)
{
    double x1, x2, x3, y1, y2, y3;
    x1 = tri.Vertex[0].x;
    x2 = tri.Vertex[1].x;
    x3 = tri.Vertex[2].x;
    y1 = tri.Vertex[0].y;
    y2 = tri.Vertex[1].y;
    y3 = tri.Vertex[2].y;

    double c = 2 * ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1));

    double x = ((y3 - y1) * (pow(x2, 2) - pow(x1, 2) + pow(y2, 2) - pow(y1, 2)) +
                (y1 - y2) * (pow(x3, 2) - pow(x1, 2) + pow(y3, 2) - pow(y1, 2))) /
               c;
    double y = ((x1 - x3) * (pow(x2, 2) - pow(x1, 2) + pow(y2, 2) - pow(y1, 2)) +
                (x2 - x1) * (pow(x3, 2) - pow(x1, 2) + pow(y3, 2) - pow(y1, 2))) /
               c;

    center = NewVec(x, y);
    radius = Dist(tri.Vertex[0], center);
}

void Circle::CalcCircle(Triangle &tri)
{
    double x1, x2, x3, y1, y2, y3;
    x1 = tri.Vertex[0].x;
    x2 = tri.Vertex[1].x;
    x3 = tri.Vertex[2].x;
    y1 = tri.Vertex[0].y;
    y2 = tri.Vertex[1].y;
    y3 = tri.Vertex[2].y;

    double c = 2 * ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1));

    double x = ((y3 - y1) * (pow(x2, 2) - pow(x1, 2) + pow(y2, 2) - pow(y1, 2)) +
                (y1 - y2) * (pow(x3, 2) - pow(x1, 2) + pow(y3, 2) - pow(y1, 2))) /
               c;
    double y = ((x1 - x3) * (pow(x2, 2) - pow(x1, 2) + pow(y2, 2) - pow(y1, 2)) +
                (x2 - x1) * (pow(x3, 2) - pow(x1, 2) + pow(y3, 2) - pow(y1, 2))) /
               c;

    center = NewVec(x, y);
    radius = Dist(tri.Vertex[0], center);
}
#include "Triangle.hpp"

Triangle::Triangle(PVector v1, PVector v2, PVector v3)
{
    Vertex.clear();
    Vertex.push_back(v1);
    Vertex.push_back(v2);
    Vertex.push_back(v3);

    Edges.clear();
    Edges.push_back(vector<PVector>{v1, v2});
    Edges.push_back(vector<PVector>{v2, v3});
    Edges.push_back(vector<PVector>{v3, v1});
}

bool Triangle::includePoint(const PVector &P)
{
    PVector A = Vertex[0];
    PVector B = Vertex[1];
    PVector C = Vertex[2];
    PVector AB = B - A;
    PVector BP = P - B;
    PVector BC = C - B;
    PVector CP = P - C;
    PVector CA = A - C;
    PVector AP = P - A;

    // Calculate cross product.
    double c1 = AB.x * BP.y - AB.y * BP.x;
    double c2 = BC.x * CP.y - BC.y * CP.x;
    double c3 = CA.x * AP.y - CA.y * AP.x;

    if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0))
    {
        return true;
    }
    return false;
}

bool Triangle::isVertex(const PVector &P)
{
    if (Vertex[0] == P || Vertex[1] == P || Vertex[2] == P)
    {
        return true;
    }
    return false;
}
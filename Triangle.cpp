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

bool Triangle::isEdge(const vector<PVector> &AB)
{
    PVector A = AB[0];
    PVector B = AB[1];
    for (int i = 0; i < 3; i++)
    {
        if ((Edges[i][0] == A && Edges[i][1] == B) || (Edges[i][0] == B && Edges[i][1] == A))
        {
            return true;
        }
    }
    return false;
}

PVector Triangle::otherVertex(const vector<PVector> &AB)
{
    if (!isEdge(AB))
    {
        cout << "Error when using Triangle::otherVertex()." << endl;
        exit(0);
    }
    PVector A = AB[0];
    PVector B = AB[1];
    int index_otherAB = -1;
    for (int i = 0; i < 3; i++)
    {
        if (Vertex[i] != A && Vertex[i] != B)
        {
            index_otherAB = i;
            break;
        }
    }
    return Vertex[index_otherAB];
}

bool Triangle::operator==(const Triangle &tri)
{
    return (this->isVertex(tri.Vertex[0]) && this->isVertex(tri.Vertex[1]) && this->isVertex(tri.Vertex[2]));
}
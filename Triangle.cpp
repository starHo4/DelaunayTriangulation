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

PVector Triangle::findVertex(PVector v1, PVector v2)
{
    PVector out = NewVec(0, 0);
    vector<int> array{0, 1, 2};
    for (int i = 0; i < array.size(); i++)
    {
        if (Vertex[i] == v1)
        {
            array.erase(array.begin() + i);
        }
    }
    for (int i = 0; i < array.size(); i++)
    {
        if (Vertex[array[i]] == v2)
        {
            array.erase(array.begin() + i);
        }
    }
    out = Vertex[array[0]];
    return out;
}

bool Triangle::includeEdge(vector<PVector> AB)
{
    PVector A = AB[0];
    PVector B = AB[1];
    bool includeA = false;
    bool includeB = false;
    for (int i = 0; i < 3; i++)
    {
        if (Vertex[i] == A)
        {
            includeA = true;
        }
        if (Vertex[i] == B)
        {
            includeB = true;
        }
    }
    if (includeA && includeB)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Triangle::generate(mt19937_64 &mt, const int w, const int h)
{
    // uniform integer distribution
    uniform_int_distribution<int> uid_w(0, w);
    uniform_int_distribution<int> uid_h(0, h);

    // Genearate triangle whose area is not 0.
    Vertex.clear();
    bool isTriangle = false;
    while (!isTriangle)
    {
        if (Vertex.size() < 2)
        {
            Vertex.push_back(NewVec(uid_w(mt), uid_h(mt)));
            continue;
        }
        int x1, x2, y1, y2, x3, y3;
        x1 = Vertex[0].x;
        x2 = Vertex[1].x;
        y1 = Vertex[0].y;
        y2 = Vertex[1].y;
        x3 = uid_w(mt);
        y3 = uid_h(mt);
        double S = abs((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2;
        if (S > 0)
        {
            Vertex.push_back(NewVec(x3, y3));
            isTriangle = true;
        }
    }
}
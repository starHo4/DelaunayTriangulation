#ifndef __Triangle__
#define __Triangle__

#include "Header.hpp"

class Triangle
{
private:
    unsigned int VERTEX_NUM = 3;

public:
    // Constructors
    Triangle() {}
    Triangle(PVector v1, PVector v2, PVector v3);

    // Getter
    unsigned int getVertexNum() { return VERTEX_NUM; };

    // Vertexes
    vector<PVector> Vertex;
    // Edges
    vector<vector<PVector>> Edges;

    // Judge whether or not this triangle includes a point.
    bool includePoint(const PVector &point);

    // Judge whether or not this triangle have P as a vertex.
    bool isVertex(const PVector &point);
};

#endif
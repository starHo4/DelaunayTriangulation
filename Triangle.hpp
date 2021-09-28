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

    PVector findVertex(PVector v1, PVector v2);
    bool includeEdge(vector<PVector> AB);

    // Triangle generation
    void generate(mt19937_64 &mt, const int w, const int h);
};

#endif
#ifndef __Game__
#define __Game__

#include "Header.hpp"

struct Parameter;
class Triangle;
class Circle;
class Flock;

class Game
{
public:
    Game();
    void Run();

private:
    // SFML
    sf::RenderWindow window;

    // Parameter
    Parameter *param;
    // Global random generator
    mt19937_64 mt;

    // Triangle
    vector<Triangle> triangles;
    // Circumscribed circle
    vector<Circle> circles;

    // Flock (Pointer)
    Flock *flock;

    // Main Functions
    void MainProcess();
    void HandleInput();
    void Render();
    void MakeDelaunay();
    void MakeInitTriangle();
    void DrawTri();
    void DrawCircle();
    void DrawFlock();
};

#endif
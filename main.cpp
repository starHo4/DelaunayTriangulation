#include "Header.hpp"

int main()
{
    Game game;
    game.Run();

    // For test
    Triangle tri1(PVector(0, 0), PVector(0, 10), PVector(10, 0));
    Triangle tri2(PVector(0, 0), PVector(10, 0), PVector(0, 10));
    if (tri1 == tri2)
    {
        cout << "hoshi" << endl;
    }
    else
    {
        cout << "hiroyuki" << endl;
    }

    return 0;
}
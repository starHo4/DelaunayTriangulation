#include "Header.hpp"

int main()
{
    Game game;
    game.Run();

    // For test
    PVector A = NewVec(1, 1);
    PVector B = NewVec(1, 1);
    if (A == B)
    {
        cout << "hoshi" << endl;
    }

    return 0;
}
#include "Header.hpp"

bool isEven(int x)
{
    if (x % 2 == 0)
    {
        return true;
    }
    return false;
}

int main()
{
    Game game;
    game.Run();

    // For test
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // auto rmif = remove_if(v.begin(), v.end(), isEven);
    // v.erase(rmif, v.end());
    auto itr = v.begin();
    while(itr != v.end()){
        if(isEven(*itr)){
            itr = v.erase(itr);
        }
        else
        {
            itr++;
        }
    }
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }

    return 0;
}
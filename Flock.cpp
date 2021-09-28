#include "Flock.hpp"

void Flock::addAgent(const Agent &a)
{
    flock.push_back(std::move(a));
}

void Flock::flocking(mt19937_64 &mt)
{
    for (int i = 0; i < flock.size(); i++)
    {
        flock[i].move(mt);
    }
}
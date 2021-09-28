#ifndef __Flock__
#define __Flock__

#include "Header.hpp"

class Flock
{
public:
    // Main body
    vector<Agent> flock;
    // Constructor
    Flock() {}
    // Getter
    Agent getAgent(int i) { return flock[i]; };
    // Add agent into flock
    void addAgent(const Agent &a);
    // Main function
    void flocking(mt19937_64 &mt);
};

#endif
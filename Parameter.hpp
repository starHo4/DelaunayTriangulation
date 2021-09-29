#ifndef __Parameter__
#define __Parameter__

struct Parameter
{
    // Constructor
    Parameter(){}

    // Random seed
    const unsigned int RANDOM_SEED = 213;

    // Parameter
    const unsigned int maxTimesteps = 1000;
    const unsigned int N = 15;

    // For SFML
    const unsigned int FPS = 10;
    const double FIELD_W = 1200;
    const double FIELD_H = 1200;

    // Agent
    const double s = 2.0; // Speed
};

#endif

#include "Agent.hpp"

void Agent::init(mt19937_64 &mt, const double w, const double h, const double s)
{
    uniform_real_distribution<double> udd_FW(0, w);
    uniform_real_distribution<double> udd_FH(0, h);
    uniform_real_distribution<double> udd_2pi(0, 2 * PI);

    pos = NewVec(udd_FW(mt), udd_FH(mt));
    angle = udd_2pi(mt);
    dir = NewVec(cos(angle), sin(angle));
    speed = s;
}

void Agent::move(mt19937_64 &mt)
{
    uniform_real_distribution<double> udd_2pi(0, 2 * PI);
    angle = udd_2pi(mt);
    dir = NewVec(cos(angle), sin(angle));

    PVector vel = NewVec(dir.x, dir.y);
    Mult(vel, speed);
    pos = Add(pos, vel);
}
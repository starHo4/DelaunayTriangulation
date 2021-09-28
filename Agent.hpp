#ifndef __Agent__
#define __Agent__

#include "HeaderBase.hpp"

class Agent
{
public:
    // Constructor;
    Agent() {}

    // Getter
    PVector getPos() { return pos; };
    PVector getDir() { return dir; };
    double getAngle() { return angle; };
    double getSpeed() { return speed; };
    // Setter
    void setPos(PVector p) { pos = p; };
    void setDir(PVector d) { dir = d; };
    void setAngle(double a) { angle = a; };
    void setSpeed(double s) { speed = s; };

    // Methods //
    void init(mt19937_64 &mt, const double w, const double h, const double s);
    void move(mt19937_64 &mt);

private:
    PVector pos;
    PVector dir;
    double angle;
    double speed;
};

#endif
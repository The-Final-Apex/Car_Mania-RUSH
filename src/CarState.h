#ifndef CARSTATE_H
#define CARSTATE_H

#include "PhysicsEngine.h"

struct CarState {
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    double rotation;        // in radians
    double steeringAngle;
    double throttle;        // 0 to 1
    double brake;           // 0 to 1
    double enginePower;
    double brakePower;
    double mass;
    double dragArea;
    
    CarState() : rotation(0), steeringAngle(0), throttle(0), brake(0),
                enginePower(0), brakePower(0), mass(0), dragArea(0) {}
};

#endif

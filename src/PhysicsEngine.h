#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "CarState.h"
#include "TrackData.h"
#include <cmath>

struct Vector2D {
    double x, y;
    
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    double length() const {
        return std::sqrt(x*x + y*y);
    }
    
    Vector2D normalize() const {
        double len = length();
        if (len > 0) return Vector2D(x/len, y/len);
        return Vector2D(0, 0);
    }
};

class PhysicsEngine {
private:
    const double GRAVITY = 9.81;
    const double AIR_DENSITY = 1.2;
    const double DRAG_COEFFICIENT = 0.3;
    const double FRICTION_COEFFICIENT = 0.8;
    
public:
    void initialize();
    void updateCarPhysics(CarState& carState);
    void checkCollisions(CarState& carState, const TrackData& track);
    Vector2D calculateForces(const CarState& carState);
};

#endif

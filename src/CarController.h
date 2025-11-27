#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H

#include "CarState.h"

class CarController {
private:
    CarState carState;
    double steeringSensitivity;
    
public:
    void initialize();
    void processInput();
    void updateCarState(CarState& newState);
    CarState getCarState() const;
    
private:
    void handleKeyboardInput();
    void applySteering(double steeringInput);
};

#endif

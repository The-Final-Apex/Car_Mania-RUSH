#include "CarController.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void CarController::initialize() {
    carState.position = Vector2D(0, 0);
    carState.velocity = Vector2D(0, 0);
    carState.acceleration = Vector2D(0, 0);
    carState.rotation = 0;
    carState.steeringAngle = 0;
    carState.throttle = 0;
    carState.brake = 0;
    carState.enginePower = 800.0;
    carState.brakePower = 1200.0;
    carState.mass = 1200.0;
    carState.dragArea = 2.2;
    
    steeringSensitivity = 0.05;
}

void CarController::processInput() {
    handleKeyboardInput();
}

void CarController::handleKeyboardInput() {
    // Simple keyboard input (you can replace with proper input system)
#ifdef _WIN32
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'w': case 'W': carState.throttle = 1.0; break;
            case 's': case 'S': carState.brake = 1.0; break;
            case 'a': case 'A': applySteering(-1.0); break;
            case 'd': case 'D': applySteering(1.0); break;
            case ' ': carState.throttle = 0; carState.brake = 0; break;
        }
    }
#else
    // Linux/Mac input handling would go here
#endif
}

void CarController::applySteering(double steeringInput) {
    carState.steeringAngle = steeringInput * steeringSensitivity;
    carState.rotation += carState.steeringAngle;
    
    // Keep rotation within 0-2π
    if (carState.rotation > 2 * M_PI) carState.rotation -= 2 * M_PI;
    if (carState.rotation < 0) carState.rotation += 2 * M_PI;
}

void CarController::updateCarState(CarState& newState) {
    carState = newState;
}

CarState CarController::getCarState() const {
    return carState;
}

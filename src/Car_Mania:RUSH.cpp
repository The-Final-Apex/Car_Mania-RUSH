//============================================================================
// Name        : Car_Mania:RUSH.cpp
// Author      : 
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Physics-based Racing Game
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>
#include "PhysicsEngine.h"
#include "CarController.h"
#include "GameRenderer.h"
#include "TrackManager.h"

class CarManiaRush {
private:
    PhysicsEngine physicsEngine;
    CarController carController;
    GameRenderer renderer;
    TrackManager trackManager;
    bool gameRunning;
    
public:
    CarManiaRush() : gameRunning(true) {}
    
    void initialize() {
        std::cout << "Initializing Car Mania: RUSH..." << std::endl;
        
        // Initialize subsystems
        physicsEngine.initialize();
        carController.initialize();
        trackManager.loadTrack("default_track");
        renderer.initialize();
        
        std::cout << "Game initialized successfully!" << std::endl;
    }
    
    void gameLoop() {
        while (gameRunning) {
            // Handle input
            handleInput();
            
            // Update game state
            update();
            
            // Render frame
            render();
            
            // Cap frame rate
            std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
        }
    }
    
    void handleInput() {
        carController.processInput();
    }
    
    void update() {
        // Update car physics
        CarState carState = carController.getCarState();
        physicsEngine.updateCarPhysics(carState);
        carController.updateCarState(carState);
        
        // Check collisions
        physicsEngine.checkCollisions(carState, trackManager.getTrackData());
        
        // Update game logic
        trackManager.update(carState);
    }
    
    void render() {
        renderer.beginFrame();
        renderer.renderTrack(trackManager.getTrackData());
        renderer.renderCar(carController.getCarState());
        renderer.renderHUD(carController.getCarState());
        renderer.endFrame();
    }
    
    void shutdown() {
        std::cout << "Shutting down Car Mania: RUSH..." << std::endl;
        renderer.cleanup();
        gameRunning = false;
    }
};

int main() {
    CarManiaRush game;
    
    try {
        game.initialize();
        game.gameLoop();
    } catch (const std::exception& e) {
        std::cerr << "Game error: " << e.what() << std::endl;
    }
    
    game.shutdown();
    return 0;
}

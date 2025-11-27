#include "GameRenderer.h"

void GameRenderer::initialize() {
    std::cout << "Renderer initialized (ASCII mode)" << std::endl;
}

void GameRenderer::beginFrame() {
    clearScreen();
}

void GameRenderer::renderTrack(const TrackData& track) {
    // Simple ASCII track rendering
    // In real implementation, use graphics library
    std::cout << "Track rendered" << std::endl;
}

void GameRenderer::renderCar(const CarState& car) {
    std::cout << "Car at (" << car.position.x << ", " << car.position.y 
              << ") Rotation: " << car.rotation << std::endl;
}

void GameRenderer::renderHUD(const CarState& car) {
    std::cout << "=== CAR MANIA: RUSH ===" << std::endl;
    std::cout << "Speed: " << car.velocity.length() * 3.6 << " km/h" << std::endl;
    std::cout << "Throttle: " << (car.throttle * 100) << "%" << std::endl;
    std::cout << "Brake: " << (car.brake * 100) << "%" << std::endl;
    std::cout << "Controls: W=Throttle, S=Brake, A=Left, D=Right, Space=Neutral" << std::endl;
}

void GameRenderer::endFrame() {
    // Frame synchronization would go here
}

void GameRenderer::cleanup() {
    std::cout << "Renderer cleaned up" << std::endl;
}

void GameRenderer::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

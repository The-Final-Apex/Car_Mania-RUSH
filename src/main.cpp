#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

class Vector2D {
public:
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

struct CarState {
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    double rotation;
    double steeringAngle;
    double throttle;
    double brake;
    double enginePower;
    double brakePower;
    double mass;
    double dragArea;
    
    CarState() : rotation(0), steeringAngle(0), throttle(0), brake(0),
                enginePower(800), brakePower(1200), mass(1200), dragArea(2.2) {}
};

class PhysicsEngine {
private:
    const double GRAVITY = 9.81;
    const double AIR_DENSITY = 1.2;
    const double DRAG_COEFFICIENT = 0.3;
    const double FRICTION_COEFFICIENT = 0.8;
    
public:
    void updateCarPhysics(CarState& carState) {
        // Calculate forces
        Vector2D forces(0, 0);
        
        // Engine force
        double engineForce = carState.enginePower * carState.throttle;
        forces.x += engineForce * std::cos(carState.rotation);
        forces.y += engineForce * std::sin(carState.rotation);
        
        // Braking force
        if (carState.brake > 0) {
            Vector2D brakeForce = carState.velocity.normalize() * (-carState.brake * carState.brakePower);
            forces = forces + brakeForce;
        }
        
        // Drag force
        double speed = carState.velocity.length();
        if (speed > 0) {
            double dragForce = 0.5 * AIR_DENSITY * DRAG_COEFFICIENT * carState.dragArea * speed * speed;
            Vector2D drag = carState.velocity.normalize() * (-dragForce);
            forces = forces + drag;
        }
        
        // Friction
        Vector2D friction = carState.velocity.normalize() * (-FRICTION_COEFFICIENT * carState.mass * GRAVITY);
        forces = forces + friction;
        
        // Update acceleration (F = ma)
        carState.acceleration.x = forces.x / carState.mass;
        carState.acceleration.y = forces.y / carState.mass;
        
        // Update velocity
        carState.velocity = carState.velocity + carState.acceleration;
        
        // Update position
        carState.position = carState.position + carState.velocity;
        
        // Apply damping
        carState.velocity = carState.velocity * 0.98;
    }
};

class CarController {
private:
    CarState carState;
    double steeringSensitivity;
    
public:
    CarController() : steeringSensitivity(0.05) {
        carState.position = Vector2D(0, 0);
    }
    
    void processInput() {
        #ifdef _WIN32
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'w': case 'W': 
                    carState.throttle = 1.0; 
                    carState.brake = 0.0;
                    break;
                case 's': case 'S': 
                    carState.brake = 1.0; 
                    carState.throttle = 0.0;
                    break;
                case 'a': case 'A': 
                    applySteering(-1.0); 
                    break;
                case 'd': case 'D': 
                    applySteering(1.0); 
                    break;
                case ' ': 
                    carState.throttle = 0.0; 
                    carState.brake = 0.0;
                    break;
                case 'q': case 'Q':
                    exit(0);
            }
        }
        #else
        // Linux input handling
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        if (ch != EOF) {
            switch (ch) {
                case 'w': case 'W': 
                    carState.throttle = 1.0; 
                    carState.brake = 0.0;
                    break;
                case 's': case 'S': 
                    carState.brake = 1.0; 
                    carState.throttle = 0.0;
                    break;
                case 'a': case 'A': 
                    applySteering(-1.0); 
                    break;
                case 'd': case 'D': 
                    applySteering(1.0); 
                    break;
                case ' ': 
                    carState.throttle = 0.0; 
                    carState.brake = 0.0;
                    break;
                case 'q': case 'Q':
                    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                    exit(0);
            }
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        #endif
    }
    
    void applySteering(double steeringInput) {
        carState.steeringAngle = steeringInput * steeringSensitivity;
        carState.rotation += carState.steeringAngle;
        
        // Keep rotation within 0-2π
        if (carState.rotation > 2 * M_PI) carState.rotation -= 2 * M_PI;
        if (carState.rotation < 0) carState.rotation += 2 * M_PI;
    }
    
    CarState& getCarState() { return carState; }
};

class GameRenderer {
public:
    void clearScreen() {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
    
    void render(const CarState& car) {
        clearScreen();
        std::cout << "=== CAR MANIA: RUSH ===" << std::endl;
        std::cout << "Position: (" << car.position.x << ", " << car.position.y << ")" << std::endl;
        std::cout << "Speed: " << car.velocity.length() * 3.6 << " km/h" << std::endl;
        std::cout << "Rotation: " << car.rotation * 180/M_PI << " degrees" << std::endl;
        std::cout << "Throttle: " << (car.throttle * 100) << "%" << std::endl;
        std::cout << "Brake: " << (car.brake * 100) << "%" << std::endl;
        std::cout << "\nControls:" << std::endl;
        std::cout << "W - Accelerate" << std::endl;
        std::cout << "S - Brake" << std::endl;
        std::cout << "A/D - Steer Left/Right" << std::endl;
        std::cout << "SPACE - Neutral" << std::endl;
        std::cout << "Q - Quit" << std::endl;
        std::cout << "=======================" << std::endl;
    }
};

int main() {
    PhysicsEngine physics;
    CarController car;
    GameRenderer renderer;
    
    std::cout << "Starting Car Mania: RUSH..." << std::endl;
    std::cout << "Game is running! Use controls to drive." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    while (true) {
        // Handle input
        car.processInput();
        
        // Update physics
        physics.updateCarPhysics(car.getCarState());
        
        // Render
        renderer.render(car.getCarState());
        
        // Cap frame rate
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 20 FPS
    }
    
    return 0;
}

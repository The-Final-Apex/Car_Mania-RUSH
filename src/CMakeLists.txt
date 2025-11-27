cmake_minimum_required(VERSION 3.10)
project(Car_Mania_RUSH)

set(CMAKE_CXX_STANDARD 11)

# Add executable
add_executable(CarManiaRush 
    Car_Mania-RUSH.cpp
    PhysicsEngine.cpp
    CarController.cpp
    GameRenderer.cpp
    TrackManager.cpp
)

# Compiler specific settings
if(MSVC)
    target_compile_options(CarManiaRush PRIVATE /W4)
else()
    target_compile_options(CarManiaRush PRIVATE -Wall -Wextra)
endif()

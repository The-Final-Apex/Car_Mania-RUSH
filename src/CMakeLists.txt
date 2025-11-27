cmake_minimum_required(VERSION 3.10)
project(Car_Mania_RUSH)

set(CMAKE_CXX_STANDARD 11)

# Add executable
add_executable(CarManiaRush main.cpp)

# Compiler specific settings
if(MSVC)
    target_compile_options(CarManiaRush PRIVATE /W4)
else()
    target_compile_options(CarManiaRush PRIVATE -Wall -Wextra)
    target_link_libraries(CarManiaRush m)  # Link math library for linux (Which is what im using for ts atm)
endif()

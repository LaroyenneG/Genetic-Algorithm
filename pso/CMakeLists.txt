cmake_minimum_required(VERSION 3.13)
project(PSO)

set(CMAKE_CXX_STANDARD 17)


add_executable(PSO example/main.cpp src/Particle.h src/Particle.cpp src/ParticleSwarmOptimization.h src/ParticleSwarmOptimization.cpp)

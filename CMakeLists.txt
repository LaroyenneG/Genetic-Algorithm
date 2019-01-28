cmake_minimum_required(VERSION 3.13)
project(Genetic_Algorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(Genetic_Algorithm src/Population.h src/Nursery.h exemple/main.cpp exemple/CardDispatcher.cpp exemple/CardDispatcher.h exemple/Packet.cpp exemple/Packet.h)
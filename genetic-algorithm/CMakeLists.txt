cmake_minimum_required(VERSION 3.13)
project(Genetic_Algorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)

include_directories(src)

add_executable(Genetic_Algorithm src/Population.h src/Nursery.h exemple/main.cpp exemple/card/CardDispatcher.cpp exemple/card/CardDispatcher.h exemple/card/Packet.cpp exemple/card/Packet.h exemple/queen/Board.cpp exemple/queen/Board.h exemple/queen/QueenSetter.h exemple/queen/QueenSetter.cpp machine/Machine.cpp machine/Machine.h machine/main.cpp)

add_executable(Machines src/Nursery.h src/Population.h machine/Machine.cpp machine/Machine.h machine/virtual-processor.c machine/virtual-processor.h machine/main.cpp machine/MachineBuilder.cpp machine/MachineBuilder.h)

target_link_libraries(Machines pthread)
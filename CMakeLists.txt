cmake_minimum_required(VERSION 3.0)

project(BattleShip)

include_directories(${CMAKE_SOURCE_DIR})



add_executable(game main.cpp board.h board.cpp player.h player.cpp ship.h ship.cpp coordinates.h coordinates.cpp ceil.h ceil.cpp)

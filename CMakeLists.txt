cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

project(BattleShip)

include_directories(${CMAKE_SOURCE_DIR})


add_executable(game main.cpp board.h board.cpp player.h player.cpp ship.h ship.cpp coordinates.h coordinates.cpp square.h square.cpp
        mark.h mark.cpp Registration_system.cpp Registration_system.h Command.cpp Command.h player_data.cpp player_data.h GameSession.cpp GameSession.h ConsoleInterface.cpp ConsoleInterface.h CommonInterface.cpp CommonInterface.h)

cmake_minimum_required(VERSION 3.20)
project(Modern_Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Modern_Chess
        main.cpp
        src/Board.cpp src/Player.cpp src/Game.cpp)

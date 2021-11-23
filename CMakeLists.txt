cmake_minimum_required(VERSION 3.20)
project(Modern_Chess)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -pedantic -g)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options(-stdlib=libstdc++)
    endif ()
endif ()

set(SOURCES
        main.cpp
        src/Board.cpp src/Player.cpp src/Game.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

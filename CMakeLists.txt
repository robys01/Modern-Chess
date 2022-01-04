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

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Faculta/SFML/lib/cmake/SFML")

set(SOURCES
        main.cpp
        src/Game.cpp src/Board.cpp src/Piece.cpp src/Textures.cpp src/ChessExceptions.cpp)

set(CMAKE_INSTALL_PREFIX artifacts)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)


install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)

cmake_minimum_required(VERSION 3.15)
project(Modern_Chess)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options("/W4" "/permissive-")
else ()
    add_compile_options("-Wall" "-Wextra" "-pedantic" "-g")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libstdc++")
    endif ()
endif ()

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2888d9c56eba4dedb93a84a3c57957e4a907d428 # master as of 2021-11-18
)

FetchContent_MakeAvailable(SFML)

set(SOURCES
        main.cpp
        src/Game.cpp src/Board.cpp src/Piece.cpp src/Textures.cpp src/ChessExceptions.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY resources DESTINATION bin)
install(FILES board.txt DESTINATION bin)

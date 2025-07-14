cmake_minimum_required(VERSION 3.26)
project(randomness LANGUAGES CXX)

include(../cmake/common.cmake)

add_executable(${PROJECT_NAME}_main
        src/main.cpp
        src/random_walker.cpp)
target_link_libraries(${PROJECT_NAME}_main PRIVATE SFML::Graphics)

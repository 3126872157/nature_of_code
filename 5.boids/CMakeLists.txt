cmake_minimum_required(VERSION 3.26)
project(boids LANGUAGES CXX)

#include(../cmake/common.cmake)

set(SFML_DIR "D:/DevEnv/Libraries/SFML-3.0.2")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}_main ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}_main PRIVATE SFML::Graphics)

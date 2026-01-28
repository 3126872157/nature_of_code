cmake_minimum_required(VERSION 3.21)
project(forces LANGUAGES CXX)

include(../cmake/common.cmake)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}_main ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}_main PRIVATE SFML::Graphics)
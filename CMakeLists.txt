#全局 CMake 配置
cmake_minimum_required(VERSION 3.25)
project(nature_of_code LANGUAGES CXX)

#引入全局配置
include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)

#添加子文件夹的章节
add_subdirectory(0.randomness)
add_subdirectory(2.forces)
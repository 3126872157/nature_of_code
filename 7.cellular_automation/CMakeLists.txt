cmake_minimum_required(VERSION 3.21)
project(cellular_automation LANGUAGES CXX)

# 尝试静态链接 SFML
# 注意：这必须在 find_package(SFML) 之前设置，但由于 find_package 在 common.cmake 里
# 我们需要在 include 之前设置它。
set(SFML_STATIC_LIBRARIES TRUE)

include(../cmake/common.cmake)

file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}_main ${SRC_FILES})

# 链接 SFML
target_link_libraries(${PROJECT_NAME}_main PRIVATE SFML::Graphics)

# 针对 MinGW 的静态链接选项，去除对 libgcc_s_seh-1.dll 和 libstdc++-6.dll 的依赖
if(MINGW)
    target_link_options(${PROJECT_NAME}_main PRIVATE -static)
endif()

# 如果是静态链接，SFML 需要定义 SFML_STATIC 宏
if(SFML_STATIC_LIBRARIES)
    target_compile_definitions(${PROJECT_NAME}_main PRIVATE SFML_STATIC)
endif()

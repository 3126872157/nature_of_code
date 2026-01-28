#共用顶层 CMake 配置

#设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(OS "win32")
    set(SFML_DIR "D:/DevEnv/Libraries/SFML-3.0.2")
    find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
elseif (UNIX AND NOT APPLE)
    set(OS "linux")
    #可执行文件输出目录
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    #SFML 库拉取配置
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 3.0.1
            GIT_SHALLOW ON
            #EXCLUDE_FROM_ALL
            SYSTEM)
    FetchContent_MakeAvailable(SFML)
    
    # --- 统一别名映射 ---
    if (TARGET sfml-graphics AND NOT TARGET SFML::Graphics)
        add_library(SFML::Graphics ALIAS sfml-graphics)
        add_library(SFML::Window ALIAS sfml-window)
        add_library(SFML::System ALIAS sfml-system)
    endif()
endif ()

message("OS is ${OS}")

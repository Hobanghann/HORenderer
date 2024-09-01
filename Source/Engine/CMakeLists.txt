cmake_minimum_required(VERSION 3.20)

project(EngineModule)

add_library(
    engine
    STATIC
    src/CameraObject.cpp
    src/EngineInputHandler.cpp
    src/GameEngine.cpp)

target_include_directories(engine PUBLIC ../Main/include)
target_link_libraries(engine PUBLIC headers)
target_link_directories(engine PUBLIC ../Main/bin)
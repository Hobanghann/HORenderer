cmake_minimum_required(VERSION 3.20)

project(RenderModule)

add_library(
    render
    STATIC
    src/RenderingPipeline.cpp)

target_include_directories(render PUBLIC ../Main/include)
target_link_libraries(render PUBLIC headers)
target_link_directories(render PUBLIC ../Main/bin)
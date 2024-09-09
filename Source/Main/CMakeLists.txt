cmake_minimum_required(VERSION 3.20)

project(
    MainModule
    LANGUAGES CXX
    )

add_library(headers STATIC src/Headers.cpp)

target_include_directories(headers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(headers PUBLIC ../Math/include)
target_include_directories(headers PUBLIC ../Resource/include)
target_include_directories(headers PUBLIC ../Render/include)
target_include_directories(headers PUBLIC ../Engine/include)

target_link_libraries(headers PUBLIC SDL2::SDL2 SDL2::SDL2main)

file(GLOB MAIN_HEADER
    "${CMAKE_CURRENT_SOURCE_DIR}/Headers.h")

file(GLOB MAIN_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

source_group("include" FILES ${MAIN_HEADER})
source_group("source" FILES ${MAIN_SOURCE})

add_subdirectory(../Math
../Math/bin)
add_subdirectory(../Resource
../Resource/bin)
add_subdirectory(../Render
../Render/bin)
add_subdirectory(../Engine
../Engine/bin)
cmake_minimum_required(VERSION 3.20)

project(MathModule)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(
    MathModule 
    STATIC
    ${SOURCES}
    ${HEADERS}
    )

target_link_libraries(MathModule PUBLIC SDL2::SDL2 SDL2::SDL2main)
target_include_directories(MathModule PUBLIC ../Main/include)

source_group("Source" REGULAR_EXPRESSION "src/.*\\.cpp")
source_group("Include" REGULAR_EXPRESSION "include/.*\\.h")
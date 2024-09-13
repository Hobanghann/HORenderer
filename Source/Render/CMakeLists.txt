cmake_minimum_required(VERSION 3.20)

project(RenderModule)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(
    RenderModule
    STATIC
    ${SOURCES}
    ${HEADERS}
    )

target_include_directories(RenderModule PUBLIC ../Math/include)
target_include_directories(RenderModule PUBLIC ../Resource/include)

target_link_libraries(RenderModule PUBLIC MathModule)
target_link_libraries(RenderModule PUBLIC ResourceModule)

target_link_directories(RenderModule PUBLIC ../Math/bin)
target_link_directories(RenderModule PUBLIC ../Resource/bin)

source_group("Source" REGULAR_EXPRESSION "src/.*\\.cpp")
source_group("Include" REGULAR_EXPRESSION "include/.*\\.h")
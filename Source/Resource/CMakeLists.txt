cmake_minimum_required(VERSION 3.20)

project(ResourceModule)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(
    ResourceModule
    STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(ResourceModule PUBLIC ../Main/include)
target_link_libraries(ResourceModule PUBLIC MathModule)
target_link_directories(ResourceModule PUBLIC ../Math/bin)

source_group("Source" REGULAR_EXPRESSION "src/.*\\.cpp")
source_group("Include" REGULAR_EXPRESSION "include/.*\\.h")
cmake_minimum_required(VERSION 3.20)

project(EngineModule)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(
    EngineModule
    STATIC
    ${SOURCES}
    ${HEADERS}
    )

    target_include_directories(EngineModule PUBLIC ../Math/include)
    target_include_directories(EngineModule PUBLIC ../Resource/include)
    target_include_directories(EngineModule PUBLIC ../Render/include)
    
    target_link_libraries(EngineModule PUBLIC MathModule)
    target_link_libraries(EngineModule PUBLIC ResourceModule)
    target_link_libraries(EngineModule PUBLIC RenderModule)
    
    target_link_directories(EngineModule PUBLIC ../Math/bin)
    target_link_directories(EngineModule PUBLIC ../Resource/bin)
    target_link_directories(EngineModule PUBLIC ../Render/bin)

source_group("Source" REGULAR_EXPRESSION "src/.*\\.cpp")
source_group("Include" REGULAR_EXPRESSION "include/.*\\.h")
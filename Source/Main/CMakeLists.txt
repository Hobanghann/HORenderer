cmake_minimum_required(VERSION 3.20)

project(
    MainModule
    LANGUAGES CXX
    )

    file(GLOB SOURCES "src/*.cpp")
    file(GLOB HEADERS "include/*.h")

add_executable(
    HORenderer 
    ${SOURCES} 
    ${HEADERS})

target_include_directories(HORenderer PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(HORenderer PUBLIC ../Math/include)
target_include_directories(HORenderer PUBLIC ../Resource/include)
target_include_directories(HORenderer PUBLIC ../Render/include)
target_include_directories(HORenderer PUBLIC ../Engine/include)


target_link_libraries(HORenderer PUBLIC SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(HORenderer PUBLIC MathModule)
target_link_libraries(HORenderer PUBLIC ResourceModule)
target_link_libraries(HORenderer PUBLIC RenderModule)
target_link_libraries(HORenderer PUBLIC EngineModule)

add_subdirectory(../Math
../Math/bin)
add_subdirectory(../Resource
../Resource/bin)
add_subdirectory(../Render
../Render/bin)
add_subdirectory(../Engine
../Engine/bin)

source_group("Source" REGULAR_EXPRESSION "src/.*\\.cpp")
source_group("Include" REGULAR_EXPRESSION "include/.*\\.h")
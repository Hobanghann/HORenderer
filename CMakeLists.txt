cmake_minimum_required(VERSION 3.20)

project(
    HORenderer
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(
    SDL2
    CONFIG
    REQUIRED
    PATHS C:/Users/zghdl/Desktop/Repository/HORenderer/Source/SDL2-2.30.5
)

if(NOT WIN32)
	message(FATAL_ERROR "This project only supports windows environment.")
endif()

if(NOT MSVC)
	message(FATAL_ERROR "This project only supports MSVC project.")
endif()

add_subdirectory(Source/Main)







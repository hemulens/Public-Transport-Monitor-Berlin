cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

# project name
project(AirTraffic VERSION 1.0)

find_package(cpprestsdk REQUIRED)
#find_package(openssl REQUIRED)
#include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/)

file(GLOB project_SRCS src/*.cpp)

# add the executable
add_executable(AirTraffic src/main.cpp)

target_link_libraries(AirTraffic PRIVATE cpprestsdk::cpprest)

target_include_directories(AirTraffic PUBLIC "${PROJECT_BINARY_DIR}")
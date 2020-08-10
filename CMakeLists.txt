cmake_minimum_required(VERSION 3.9)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(Air-Traffic-Monitor VERSION 1.0)
add_executable(
  airtraffic 
  src/Controller.cpp
)
# add_executable(airtraffic ${project_SRCS})
include_directories(src)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)
#include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/)

#file(GLOB project_SRCS src/*.cpp)

target_link_libraries(airtraffic PRIVATE cpprestsdk::cpprest)

target_include_directories(airtraffic PUBLIC "${PROJECT_BINARY_DIR}")
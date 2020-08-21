cmake_minimum_required(VERSION 3.9)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

project(Public-Transport-Monitor VERSION 1.0)
add_executable(
  BerlinTransport 
  src/Controller.cpp
)
# add_executable(BerlinTransport ${project_SRCS})
# file(GLOB project_SRCS src/*.cpp) #src/*.h
include_directories(src)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(OpenCV 4.1 REQUIRED)
#include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})


#file(GLOB project_SRCS src/*.cpp)

target_link_libraries(BerlinTransport PRIVATE cpprestsdk::cpprest ${OpenCV_LIBRARIES})

target_include_directories(BerlinTransport PUBLIC "${PROJECT_BINARY_DIR}")
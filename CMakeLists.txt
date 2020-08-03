cmake_minimum_required(VERSION 3.9)
project(monitor)

find_package(cpprestsdk REQUIRED)

add_executable(monitor main.cpp)
target_link_libraries(monitor PRIVATE cpprestsdk::cpprest)
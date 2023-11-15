
cmake_minimum_required(VERSION 3.8...3.27)

project(HelloWorld)


add_executable(HelloWorld main.cpp)

target_link_libraries(HelloWorld PRIVATE NGIN)


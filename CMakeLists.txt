set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
cmake_minimum_required(VERSION 3.8...3.27)

project("NGIN" VERSION 0.1)

# enable c and c++
enable_language(C CXX)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)


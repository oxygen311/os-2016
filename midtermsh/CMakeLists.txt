cmake_minimum_required(VERSION 3.5)
project(midterm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES midtermsh.cpp)
add_executable(midterm ${SOURCE_FILES})

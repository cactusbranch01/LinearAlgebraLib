
cmake_minimum_required(VERSION 3.24)
project(AI)

set(CMAKE_CXX_STANDARD 17)

add_executable(AI main.cpp VectorGeometry.cpp LinearRegression.cpp LinearRegression.h VectorGeometry.h testing.h testing.cpp)

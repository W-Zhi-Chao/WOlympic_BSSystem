cmake_minimum_required(VERSION 3.20)
project(WOlympic_BSSystem)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_executable(WOlympic_BSSystem SQL.cpp calculator.cpp main.cpp Commodity.cpp core.cpp Order.cpp)

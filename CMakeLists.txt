cmake_minimum_required(VERSION 3.17)
project(gooseEscape)

set(CMAKE_CXX_STANDARD 11)
include_directories(BearLibTerminal_0.15.7/Include/C)

add_executable(gooseEscape gooseEscapeMain.cpp gooseEscapeGamePlay.cpp)
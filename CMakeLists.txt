cmake_minimum_required(VERSION 3.17)
project(gooseEscape)

set(CMAKE_CXX_STANDARD 11 )
include_directories(BearLibTerminal_0.15.7/Include/C)
link_directories(BearLibTerminal_0.15.7/Linux64)

add_executable(gooseEscape gooseEscapeMain.cpp gooseEscapeGamePlay.cpp)
target_link_libraries(gooseEscape libBearLibTerminal.so)

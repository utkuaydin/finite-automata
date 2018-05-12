cmake_minimum_required(VERSION 3.10)
project(RegexEngine)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(RegexEngine Edge.cpp Edge.h InfixToPostfixConverter.cpp InfixToPostfixConverter.h NFA.cpp NFA.h Engine.cpp Engine.h main.cpp)

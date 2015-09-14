cmake_minimum_required(VERSION 3.2)
project(SimpleDBChallenge)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(SimpleDBChallenge ${SOURCE_FILES} src/Database.cpp src/Database.h src/Command.cpp src/Command.h src/Printer.cpp src/Printer.h src/Handle.cpp src/Handle.h)
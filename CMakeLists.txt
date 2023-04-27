cmake_minimum_required(VERSION 3.24)
project(HttpServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(HttpServer src/main.cpp src/Server.cpp src/Server.h src/RequestType.h src/Detail.h src/Detail.cpp)

cmake_minimum_required(VERSION 3.24)
project(HttpServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(HttpServer src/main.cpp
        src/Server.cpp src/Server.h
        src/RequestType.h src/RequestType.cpp
        src/NetDetail.h src/NetDetail.cpp
        src/Request.cpp src/Request.h
        src/Detail.cpp src/Detail.h
        src/Response.cpp src/Response.h
        src/ResponseStatusCode.h src/ResponseStatusCode.cpp)

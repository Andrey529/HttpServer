# Build stage
FROM gcc:latest as build
WORKDIR /build

ENV BUILD_TYPE=Debug

# Install all packages
RUN apt-get update && \
    apt-get install -y cmake

ADD ./src /app/src
ADD ./pages /app/pages
ADD ./CMakeLists.txt /app

WORKDIR /app/build
# Build binaries
RUN cmake .. && \
    cmake --build .

ENTRYPOINT ["./HttpServer", "0.0.0.0", "8080"]

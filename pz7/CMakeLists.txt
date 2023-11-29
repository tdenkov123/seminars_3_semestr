cmake_minimum_required(VERSION 3.10)

project(pz7 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(pz7 src/main.cpp "src/main.cpp" "src/BMPreader.h")

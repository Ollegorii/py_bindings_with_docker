cmake_minimum_required(VERSION 3.12)
project(svd_cpp LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Python 3.10 REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 REQUIRED)

pybind11_add_module(svd_cpp
    bindings.cpp
    svd.cpp
)

target_compile_options(svd_cpp PRIVATE -O3)

install(TARGETS svd_cpp
    LIBRARY DESTINATION .
)
cmake_minimum_required(VERSION 3.12)
project(svd_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Python and pybind11
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

# Create Python module
pybind11_add_module(svd_cpp bindings.cpp svd.cpp)

# Install target
install(TARGETS svd_cpp DESTINATION svd_cpp)
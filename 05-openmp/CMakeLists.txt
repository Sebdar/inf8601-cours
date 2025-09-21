cmake_minimum_required(VERSION 4.0.0)
project(inf8601-openmp C CXX)

find_package(OpenMP)

include_directories(include)

add_executable(01-omp-parallel src/01-omp-parallel.cpp)
target_link_libraries(01-omp-parallel PUBLIC OpenMP::OpenMP_CXX)

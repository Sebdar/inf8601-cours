cmake_minimum_required(VERSION 4.0.0)
project(inf8601-opencl C CXX CUDA)

set(CMAKE_CXX_FLAGS "-ggdb")

include_directories(include)

add_custom_target(slides
    COMMAND mkdir -p slides && cd slides && latexmk -shell-escape -jobname=Chap06-OpenCL ${CMAKE_CURRENT_SOURCE_DIR}/Chap06-OpenCL.tex -pdf
    DEPENDS Chap06-OpenCL.tex
    BYPRODUCTS slides
)

find_package(OpenCL REQUIRED)
add_compile_definitions("OPENCL_KERNEL_DIR=${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(01-init-opencl 01-init-opencl.c)
target_link_libraries(01-init-opencl OpenCL::OpenCL)

add_executable(02-simple-kernel 02-simple-kernel.cpp)
target_link_libraries(02-simple-kernel OpenCL::OpenCL)

add_executable(04-cuda-simple-kernel 04-cuda-simple-kernel.cu)

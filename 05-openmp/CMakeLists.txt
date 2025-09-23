cmake_minimum_required(VERSION 4.0.0)
project(inf8601-openmp C CXX)

set(CMAKE_CXX_FLAGS "-O2 -ggdb")

find_package(OpenMP)

include_directories(include)

add_custom_target(slides
    COMMAND mkdir -p slides && cd slides && latexmk -shell-escape -jobname=Chap05-OpenMP ${CMAKE_CURRENT_SOURCE_DIR}/Chap05-OpenMP.tex -pdf
    DEPENDS Chap05-OpenMP.tex
    BYPRODUCTS slides
    )

add_executable(01-omp-parallel src/01-omp-parallel.cpp)
target_link_libraries(01-omp-parallel PUBLIC OpenMP::OpenMP_CXX)

add_executable(02-omp-parallel-critical src/02-omp-parallel-critical.cpp)
target_link_libraries(02-omp-parallel-critical PUBLIC OpenMP::OpenMP_CXX)

add_executable(03-omp-teams src/03-omp-teams.cpp)
target_link_libraries(03-omp-teams PUBLIC OpenMP::OpenMP_CXX)

add_executable(04-omp-sections src/04-omp-sections.cpp)
target_link_libraries(04-omp-sections PUBLIC OpenMP::OpenMP_CXX)

add_executable(05-omp-for src/05-omp-for.cpp)
target_link_libraries(05-omp-for PUBLIC OpenMP::OpenMP_CXX)

add_executable(06-omp-scan src/06-omp-scan.cpp)
target_link_libraries(06-omp-scan PUBLIC OpenMP::OpenMP_CXX)

add_executable(07-omp-task src/07-omp-task.cpp)
target_link_libraries(07-omp-task PUBLIC OpenMP::OpenMP_CXX)

add_executable(08-omp-simd src/08-omp-simd.cpp)
target_link_libraries(08-omp-simd PUBLIC OpenMP::OpenMP_CXX)

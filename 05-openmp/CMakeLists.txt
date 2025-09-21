cmake_minimum_required(VERSION 4.0.0)
project(inf8601-openmp C CXX)

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

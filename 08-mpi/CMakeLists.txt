cmake_minimum_required(VERSION 4.0.0)
project(inf8601-mpi C CXX)

add_custom_target(slides
    COMMAND mkdir -p slides && cd slides && latexmk -shell-escape -jobname=Chap08-MPI ${CMAKE_CURRENT_SOURCE_DIR}/Chap08-MPI.tex -pdf
    DEPENDS Chap08-MPI.tex
    BYPRODUCTS slides
)

find_package(MPI REQUIRED)

add_executable(01-hello-world 01-hello-world.c)
target_link_libraries(01-hello-world MPI::MPI_C)

add_executable(02-hello-world-ranks 02-hello-world-ranks.c)
target_link_libraries(02-hello-world-ranks MPI::MPI_C)

add_executable(03-matrix-multiply 03-matrix-multiply.c)
target_link_libraries(03-matrix-multiply MPI::MPI_C)

add_executable(04-monte-carlo-pi 04-monte-carlo-pi.cpp)
target_link_libraries(04-monte-carlo-pi MPI::MPI_C)

add_executable(05-monte-carlo-pi-reduce 05-monte-carlo-pi-reduce.cpp)
target_link_libraries(05-monte-carlo-pi-reduce MPI::MPI_C)

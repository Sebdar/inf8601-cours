cmake_minimum_required(VERSION 4.0.0)
project(inf8601-mpi C CXX)

add_custom_target(slides
    COMMAND mkdir -p slides && cd slides && latexmk -shell-escape -jobname=Chap08-MPI ${CMAKE_CURRENT_SOURCE_DIR}/Chap08-MPI.tex -pdf
    DEPENDS Chap08-MPI.tex
    BYPRODUCTS slides
)

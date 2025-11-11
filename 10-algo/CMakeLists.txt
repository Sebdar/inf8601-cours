cmake_minimum_required(VERSION 4.0.0)
project(inf8601-algo C CXX)

add_custom_target(slides
    COMMAND mkdir -p slides && cd slides && latexmk -shell-escape -jobname=Chap10-Algo ${CMAKE_CURRENT_SOURCE_DIR}/Chap10-algo.tex -pdf
    DEPENDS Chap10-algo.tex
    BYPRODUCTS slides
)

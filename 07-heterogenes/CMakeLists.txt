cmake_minimum_required(VERSION 4.0.0)
project(inf8601-heterogenes C CXX)

add_custom_target(slides
    COMMAND mkdir -p slides && cd slides && latexmk -shell-escape -jobname=Chap07-HSA ${CMAKE_CURRENT_SOURCE_DIR}/Chap07-HSA.tex -pdf
    DEPENDS Chap07-HSA.tex
    BYPRODUCTS slides
)

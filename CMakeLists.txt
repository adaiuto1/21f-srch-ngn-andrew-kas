cmake_minimum_required(VERSION 3.16)
project(21f_final_proj_template)

set(CMAKE_CXX_STANDARD 17)

include_directories(Lib)

add_executable(21f_final_proj_template main.cpp catch_setup.cpp FileReader.cpp FileReader.h DSString.cpp DSString.h
        porter2_stemmer.h porter2_stemmer.cpp AvlNode.h AvlTree.h idxHandle.h Hashtable.h)

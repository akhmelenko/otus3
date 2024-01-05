# Cmake minimal version.
cmake_minimum_required(VERSION 3.10)

project(helloworld)

add_library(helloworld STATIC lib.cpp)

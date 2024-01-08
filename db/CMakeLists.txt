# Cmake minimal version.
cmake_minimum_required(VERSION 3.10)

project(db)

add_library(db STATIC db.cpp dummy_connection.cpp)

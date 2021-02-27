cmake_minimum_required(VERSION 3.13)

cmake_policy(SET CMP0076 NEW)
target_sources(util_fpgasoc PRIVATE fpgasoc_read.cpp)
target_include_directories(util_fpgasoc PRIVATE .)


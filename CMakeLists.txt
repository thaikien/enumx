cmake_minimum_required(VERSION 3.22)

project(enumx)

add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-Werror=switch>)

add_library(enumx INTERFACE)

target_include_directories(enumx INTERFACE .)

add_subdirectory(test)

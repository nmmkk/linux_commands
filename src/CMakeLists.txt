cmake_minimum_required(VERSION 2.8)

project(rootproject)

# set(CMAKE_VERBOSE_MAKEFILE 1)

include(CheckFunctionExists)
include(CheckIncludeFiles)

# Note: An environment variable can be referred as $ENV{VARIABLE_NAME}
set(MY_COMPILE_FLAGS
    "-g -Wall -O0")

add_subdirectory(wc)
add_subdirectory(cat)
add_subdirectory(ls)
add_subdirectory(cd)


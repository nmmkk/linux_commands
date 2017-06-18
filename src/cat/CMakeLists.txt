cmake_minimum_required(VERSION 2.8)

project(cat)

# set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(cat cat.c)
set_target_properties(cat
    PROPERTIES
    COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    LINK_FLAGS ${MY_COMPILE_FLAGS}
    )


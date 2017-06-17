cmake_minimum_required(VERSION 2.8)

project(wc)

# set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(wc wc.c)
set_target_properties(wc
    PROPERTIES
    COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    LINK_FLAGS ${MY_COMPILE_FLAGS}
    )


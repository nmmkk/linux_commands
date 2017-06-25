cmake_minimum_required(VERSION 2.8)

project(mv)

# set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(mv mv.c)
set_target_properties(mv
    PROPERTIES
    COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    LINK_FLAGS ${MY_COMPILE_FLAGS}
    )


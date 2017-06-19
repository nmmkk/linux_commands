cmake_minimum_required(VERSION 2.8)

project(ls)

# set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(ls ls.c)
set_target_properties(ls
    PROPERTIES
    COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    LINK_FLAGS ${MY_COMPILE_FLAGS}
    )


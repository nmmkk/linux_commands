cmake_minimum_required(VERSION 2.8)

project(cd)

# set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(cd cd.c)
set_target_properties(cd
    PROPERTIES
    COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    LINK_FLAGS ${MY_COMPILE_FLAGS}
    )


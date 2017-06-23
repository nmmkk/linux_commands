cmake_minimum_required(VERSION 2.8)

project(pwd)

# set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(pwd pwd.c)
set_target_properties(pwd
    PROPERTIES
    COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    LINK_FLAGS ${MY_COMPILE_FLAGS}
    )


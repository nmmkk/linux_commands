cmake_minimum_required(VERSION 2.8)

project(echo)

# set(CMAKE_VERBOSE_MAKEFILE 1)

add_executable(echo echo.c)
set_target_properties(echo
    PROPERTIES
    COMPILE_FLAGS ${MY_COMPILE_FLAGS}
    LINK_FLAGS ${MY_COMPILE_FLAGS}
    )


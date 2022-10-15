cmake_minimum_required (VERSION 3.13)

project(exceptions)

target_sources(lc_client 
    PRIVATE
        "glad_exceptions.h"
        "glfw_exceptions.h"
        "input_exceptions.h"
)
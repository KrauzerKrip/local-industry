cmake_minimum_required (VERSION 3.13)

project(exceptions)

target_sources(lc_client 
    PRIVATE
        "glad_exceptions.h"
        "glfw_exceptions.h"
        "input_exceptions.h"
        "io_exceptions.h"
        "lua_exceptions.h"
        "conpar_exceptions.h"
        "command_exceptions.h"
        "graphics_exceptions.h"
        "npc_exceptions.h"
        "physics_exception.h"
)
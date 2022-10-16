cmake_minimum_required (VERSION 3.13)

project(eng_graphics)

target_sources(lc_client 
    PRIVATE
        "i_window.h"
        "i_render.h"

        "openGL/gl_render.cpp"
        "openGL/gl_render.h"
        "openGL/gl_window.cpp"
        "openGL/gl_window.h"

        "entt/components.h"
)
cmake_minimum_required (VERSION 3.13)

project(eng_procedures)

target_sources(lc_client 
    PRIVATE
        "i_shaders.h"
        "graphics_entities_loading.h"

        "openGL/shaders.h"
        "openGL/shaders.cpp"
        "openGL/gl_graphics_entities_loading.h"
        "openGL/gl_graphics_entities_loading.cpp"
        "openGL/gl_texture_manager.h"
        "openGL/gl_texture_manager.cpp"
)
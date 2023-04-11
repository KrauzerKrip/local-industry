cmake_minimum_required (VERSION 3.13)

project(eng_procedures)

target_sources(lc_client 
    PRIVATE
        "i_shaders.h"
        "graphics_entities_loading.h"
        "texture_manager.h"
        "texture_manager.cpp"

        "openGL/gl_shaders.h"
        "openGL/gl_shaders.cpp"
        "openGL/gl_graphics_entities_loading.h"
        "openGL/gl_graphics_entities_loading.cpp"
        "openGL/gl_texture_manager.h"
        "openGL/gl_texture_manager.cpp"

        "tier1/game_info.h"
        "tier1/game_info.cpp"
        "tier1/tier1.h"
        "tier1/tier1.cpp"
        "tier1/gl_tier1.h"
        "tier1/gl_tier1.cpp"
)
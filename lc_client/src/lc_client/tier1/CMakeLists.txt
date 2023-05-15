cmake_minimum_required (VERSION 3.13)

project(eng_procedures)

target_sources(lc_client 
    PRIVATE
        "i_shaders.h"
        "texture_manager.h"
        "texture_manager.cpp"

        "openGL/gl_shaders.h"
        "openGL/gl_shaders.cpp"
        "openGL/gl_texture_manager.h"
        "openGL/gl_texture_manager.cpp"
        "openGL/gl_tier1.h"
        "openGL/gl_tier1.cpp"

        "game_info.h"
        "game_info.cpp"
        "tier1.h"
        "tier1.cpp"
)
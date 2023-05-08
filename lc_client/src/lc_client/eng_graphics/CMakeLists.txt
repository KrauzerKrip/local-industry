cmake_minimum_required (VERSION 3.13)

project(eng_graphics)

target_sources(lc_client 
    PRIVATE
        "i_window.h"
        "i_render.h"
        "texture.h"
        "graphics_entities_util.h"

        "openGL/gl_render.cpp"
        "openGL/gl_render.h"
        "openGL/gl_window.cpp"
        "openGL/gl_window.h"
        "openGL/gl_texture.h"
        "openGL/gl_texture.cpp"
        "openGL/gl_graphics_entities_util.h"
        "openGL/gl_graphics_entities_util.cpp"

        "entt/components.h"

        "camera/camera.h"
        "camera/camera.cpp"

)
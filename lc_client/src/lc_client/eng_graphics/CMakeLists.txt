cmake_minimum_required (VERSION 3.13)

project(eng_graphics)

target_sources(lc_client 
    PRIVATE
        "i_window.h"
        "i_render.h"
        "texture.h"
        "mesh_work.h"
        "shader_work"
        
        "shader_system.h"
        "shader_system.cpp"
        "material_system.h"
        "material_system.cpp"

        "openGL/gl_render.cpp"
        "openGL/gl_render.h"
        "openGL/gl_window.cpp"
        "openGL/gl_window.h"
        "openGL/gl_texture.h"
        "openGL/gl_texture.cpp"
        "openGL/gl_mesh_work.h"
        "openGL/gl_mesh_work.cpp"
        "openGL/gl_shader_work.h"
        "openGL/gl_shader_work.cpp"

        "entt/components.h"

        "camera/camera.h"
        "camera/camera.cpp"

)
cmake_minimum_required (VERSION 3.13)

project(eng_graphics)

target_sources(lc_client 
    PRIVATE
        "i_window.h"
        "i_render.h"
        "texture.h"
        "mesh_work.h"
        "shader_work"
        "skybox_render.h"
        "skybox_render.cpp"
        
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
        "openGL/gl_shader_uniform.h"
        "openGL/gl_framebuffer.h"
        "openGL/gl_framebuffer.cpp"
        "openGL/gl_skybox_render.h"
        "openGL/gl_skybox_render.cpp"
        #"openGL/gl_texture_cubemap.h"
        #"openGL/gl_texture_cubemap.cpp"
        "openGL/renders/gl_render_map.h"
        "openGL/renders/gl_render_map.cpp"
        "openGL/renders/gl_lighting.h"
        "openGL/renders/gl_lighting.cpp"

        "gui/render_text.h"
        "gui/render_background.h"
        "gui/openGL/gl_render_text.h"
        "gui/openGL/gl_render_text.cpp"
        "gui/openGL/gl_render_background.h"
        "gui/openGL/gl_render_background.cpp"


        "entt/components.h"

        "camera/camera.h"
        "camera/camera.cpp"

 "openGL/gl_shader_uniform.cpp")
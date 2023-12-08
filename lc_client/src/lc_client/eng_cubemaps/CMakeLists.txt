cmake_minimum_required (VERSION 3.13)

project(util)

target_sources(lc_client 
    PRIVATE
        "cubemap_texture_loader.h"
        
        "cubemap_loader.h"
        "cubemap_texture_loader.cpp"
        "cubemap_system.h"
        "cubemap_system.cpp"

        "openGL/gl_cubemap_loader.h"
        "openGL/gl_cubemap_loader.cpp"

        "entt/components.h"
)
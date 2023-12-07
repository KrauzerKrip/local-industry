cmake_minimum_required (VERSION 3.13)

project(util)

target_sources(lc_client 
    PRIVATE
        "cubemap_work.h"
        
        "cubemap_loader.h"
        "cubemap_loader.cpp"
        "cubemap_system.h"
        "cubemap_system.cpp"

        "openGL/gl_cubemap_work.h"
        "openGL/gl_cubemap_work.cpp"

        "entt/components.h"
)
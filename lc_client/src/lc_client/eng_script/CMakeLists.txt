cmake_minimum_required (VERSION 3.13)

project(eng_script)

target_sources(lc_client 
    PRIVATE
    
    "entt/components.h"

    "lua/lua_script.h"
    "lua/lua_script.cpp"

)
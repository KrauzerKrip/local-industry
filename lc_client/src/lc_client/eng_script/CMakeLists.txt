cmake_minimum_required (VERSION 3.13)

project(eng_script)

target_sources(lc_client 
    PRIVATE
    
    "entt/components.h"

    "lua/lua_script.h"
    "lua/lua_script.cpp"

    "api/api_scene.h"
    "api/api_scene.cpp"
    "api/api.h"
    "api/api.cpp"

    "api/bindings/api_component_binding.h"
    "api/bindings/api_component_binding.cpp"
    "api/bindings/glm_binding.h"
    "api/bindings/glm_binding.cpp"
    "api/bindings/api_binding.h"
    "api/bindings/api_binding.cpp"

    "api/helpers/glm_helpers.h"
    "api/helpers/glm_helpers.cpp"
    "api/helpers/components.h"

    "script_system.h"
    "script_system.cpp"

)
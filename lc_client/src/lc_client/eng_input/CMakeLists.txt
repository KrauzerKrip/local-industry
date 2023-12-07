cmake_minimum_required (VERSION 3.13)

project(eng_input)

target_sources(lc_client 
    PRIVATE
        "i_input.h"

        "key_code.h"

        "glfw_input.h"
        "glfw_input.cpp"

        "entt/components.h"
)
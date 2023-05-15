cmake_minimum_required (VERSION 3.13)

project(eng_input)

target_sources(lc_client 
    PRIVATE
        "i_input_raw.h"

        "glfw_input_raw.cpp"
        "glfw_input_raw.h"

        "input.h"
        "input.cpp"

        "entt/components.h"
)
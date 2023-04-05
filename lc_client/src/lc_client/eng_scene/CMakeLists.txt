cmake_minimum_required (VERSION 3.13)

project(eng_procedures)

target_sources(lc_client 
    PRIVATE
    "scene.h"
    "scene.cpp"
    "scene_loading.h"
    "scene_loading.cpp"

    "entt/components.h"
)
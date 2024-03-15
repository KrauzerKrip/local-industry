cmake_minimum_required (VERSION 3.13)

project(eng_physics)

target_sources(lc_client 
    PRIVATE
        "entt/components.h"
        "physics_system.h"
        "physics_system.cpp"
        "physics_visualizer.h"
        "physics_visualizer.cpp"
        "raycast/plane.h"
        "raycast/plane.cpp"
        "raycast/ray.h"
        "raycast/ray.cpp"
        "physics.h"
        "physics.cpp"
        "physics_loading_system.h"
        "physics_loading_system.cpp"
        "physics_parser.h"
        "physics_parser.cpp"
        "physics_loader.h"
        "physics_loader.cpp"
        "collider_system.h"
        "collider_system.cpp"
)
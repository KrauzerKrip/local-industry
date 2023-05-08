cmake_minimum_required (VERSION 3.13)

project(eng_model)

target_sources(lc_client 
    PRIVATE
        "model_loading.h"
        "model_loading.cpp"
        "model_manager.h"
        "model_manager.cpp"
        "model_system.h"
        "model_system.cpp"

        "entt/components.h"

)
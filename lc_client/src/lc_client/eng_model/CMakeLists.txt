cmake_minimum_required (VERSION 3.13)

project(eng_model)

target_sources(lc_client 
    PRIVATE
        "model_loading.h"
        "model_loading.cpp"
        "model_manager.h"
        "model_manager.cpp"

        "entt/components.h"

)
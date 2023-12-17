cmake_minimum_required (VERSION 3.13)

project(eng_physics)

target_sources(lc_client 
    PRIVATE
    "npc_system.h"
    "npc_system.cpp"
    "components.h"
    "npc_graph.h"
    "npc_graph.cpp"
    "npc_graph_loader/npc_graph_loader.h"
    "npc_graph_loader/npc_graph_loader.cpp"
)
cmake_minimum_required (VERSION 3.13)

project(lc_client)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/List.h")
find_package(Lua REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)


target_link_libraries(lc_client PUBLIC glfw glad::glad EnTT::EnTT)
target_link_libraries(lc_client PUBLIC glm::glm)
target_link_libraries(lc_client PRIVATE assimp::assimp)
target_link_libraries(lc_client PRIVATE pugixml::pugixml)
target_link_libraries(lc_client PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(lc_client PRIVATE ${LUABRIDGE_INCLUDE_DIRS})
target_include_directories(lc_client PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(lc_client PRIVATE ${LUA_LIBRARIES})
target_link_libraries(lc_client PRIVATE imgui::imgui)
target_link_libraries(lc_client PRIVATE freetype)

#target_link_libraries(lc_client PRIVATE eng::rc)
target_link_libraries(lc_client PRIVATE stb)   

target_sources(lc_client 
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/i_game_logic.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/loop.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lc_client/loop.h"

        
        
 )

add_subdirectory("include/ldk_client/local_engine")

add_subdirectory("src/lc_client/local_engine")

add_subdirectory("src/lc_client/eng_graphics")
add_subdirectory("src/lc_client/eng_entties")
add_subdirectory("src/lc_client/eng_input")
add_subdirectory("src/lc_client/eng_procedures")
add_subdirectory("src/lc_client/eng_model")
add_subdirectory("src/lc_client/eng_scene")
add_subdirectory("src/lc_client/eng_lighting")
add_subdirectory("src/lc_client/eng_script")
add_subdirectory("src/lc_client/eng_gui")
add_subdirectory("src/lc_client/eng_cubemaps")
add_subdirectory("src/lc_client/eng_map")
add_subdirectory("src/lc_client/eng_debug")
add_subdirectory("src/lc_client/eng_physics")
add_subdirectory("src/lc_client/eng_systems")
add_subdirectory("src/lc_client/eng_world")
add_subdirectory("src/lc_client/tier0")
add_subdirectory("src/lc_client/tier1")
add_subdirectory("src/lc_client/exceptions")
add_subdirectory("src/lc_client/util")

#target_compile_definitions(lc_client PUBLIC USE_BARRY) #for preprocessor definitions
target_include_directories(lc_client
    PUBLIC
        $<INSTALL_INTERFACE:/include>
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

add_subdirectory("test")
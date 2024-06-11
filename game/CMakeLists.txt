cmake_minimum_required(VERSION 3.13)

project(game)

add_executable(game_exe "src/game/main.cpp" "src/game/main.h" "src/game/game.cpp" "src/game/game.h" "src/game/graphics.h" "src/game/graphics.cpp" "src/game/game_systems.h" "src/game/game_systems.cpp")
add_library(game STATIC)

add_subdirectory("src/game/gui")
add_subdirectory("src/game/loader_fabric")
add_subdirectory("src/game/camera")
add_subdirectory("src/game/control")
add_subdirectory("src/game/character")
add_subdirectory("src/game/machine")
add_subdirectory("src/game/item")
add_subdirectory("src/game/agriculture")
add_subdirectory("src/game/inventory")
add_subdirectory("src/game/economy")
add_subdirectory("src/game/resource")
add_subdirectory("src/game/util")

target_include_directories(game
    PUBLIC
        $<INSTALL_INTERFACE:/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(game_exe game)

add_subdirectory("test")
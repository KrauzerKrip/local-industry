cmake_minimum_required(VERSION 3.13)

project(gui)

add_subdirectory("dependencies_fabric")
add_subdirectory("machine_menu")
add_subdirectory("side_menu")
add_subdirectory("machine_inspector")
add_subdirectory("inventory")

target_sources(game PRIVATE
	"main_layout.h"
	"main_layout.cpp"
	"gui.h"
	"gui.cpp"

	"overlay/overlay.h"
	"overlay/overlay.cpp"
)
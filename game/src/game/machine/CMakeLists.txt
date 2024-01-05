cmake_minimum_required(VERSION 3.13)

project(machine)

add_subdirectory("blueprint")

add_subdirectory("machines")

target_sources(game PRIVATE
	"components.h"
	"machine_system.h"
	"machine_system.cpp"
	"../control/machine_control_system.h"
	"../control/machine_control_system.cpp"
 "machine_type.h"
	"machine_loader.h"
	"machine_loader.cpp"
	"machine_loading_system.h"
	"machine_loading_system.cpp"
)
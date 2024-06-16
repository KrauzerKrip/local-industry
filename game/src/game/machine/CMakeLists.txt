cmake_minimum_required(VERSION 3.13)

project(machine)

add_subdirectory("blueprint")
add_subdirectory("machines")
add_subdirectory("physics")
add_subdirectory("graphics")

target_sources(game PRIVATE
	"components.h"
	"machine_system.h"
	"machine_system.cpp"
 "machine_type.h"
 "machine_type.cpp"
	"machine_loader.h"
	"machine_loader.cpp"
	"machine_loading_system.h"
	"machine_loading_system.cpp"
	"base_machine_system.h"
	"machine_connector.h"
	"machine_connector.cpp"
	"connection_system.h"
	"connection_system.cpp"
)
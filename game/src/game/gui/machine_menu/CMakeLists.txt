cmake_minimum_required(VERSION 3.13)

project(gui_machine_menu)

target_sources(game PRIVATE
	"machine_build_menu.h"
	"machine_build_menu.cpp"
	"machine_slot.h"
	"machine_slot.cpp"
)
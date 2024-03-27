cmake_minimum_required(VERSION 3.13)

project(gui_machine_menu)

target_sources(game PRIVATE
	"machine_build_menu.h"
	"machine_build_menu.cpp"
	"machine_slot.h"
	"machine_slot.cpp"
	"machine_category_button.h"
	"machine_category_button.cpp"
	"machine_category.h"
	"machine_category.cpp"
)
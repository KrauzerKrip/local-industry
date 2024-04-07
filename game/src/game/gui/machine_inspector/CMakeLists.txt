cmake_minimum_required(VERSION 3.13)

project(gui_machine_menu)

target_sources(game PRIVATE
	"machine_inspector_view.h"
	"machine_inspector_view.cpp"
	"machine_inspector_controller.h"
	"machine_inspector_controller.cpp"
)
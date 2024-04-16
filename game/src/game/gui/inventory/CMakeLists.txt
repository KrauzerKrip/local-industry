cmake_minimum_required(VERSION 3.13)

project(gui_inventory)

target_sources(game PRIVATE
	"inventory_view.h"
	"inventory_view.cpp"
	"inventory_controller.h"
	"inventory_controller.cpp"
)
cmake_minimum_required(VERSION 3.13)

project(control)

target_sources(game PRIVATE
	#"movement_controller.h"
	#"movement_controller.cpp"
	"action_bind.h"
	"action_bind.cpp"
	"action_init.h"
	"action_init.cpp"
	"control.h"
	"control.cpp"
)
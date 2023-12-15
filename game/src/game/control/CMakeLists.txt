cmake_minimum_required(VERSION 3.13)

project(control)

target_sources(game PRIVATE
	"action_bind.h"
	"action_bind.cpp"
	"action_init.h"
	"action_init.cpp"
	"action_control.h"
	"action_control.cpp"
	"components.h"
	"mouse_raycast_system.h"
	"mouse_raycast_system.cpp"
 "mouse_raycast_observer.h"
 "selection_system.h"
 "selection_system.cpp"
 
 
)
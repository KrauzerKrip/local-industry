cmake_minimum_required(VERSION 3.28)

project(control)

target_sources(game PRIVATE
	"action_bind.h"
	"action_bind.cpp"
	
	
	"action_control.h"
	"action_control.cpp"
	"components.h"
	"mouse_raycast_system.h"
	"mouse_raycast_system.cpp"
 "mouse_raycast_observer.h"
 "selection_system.h"
 "selection_system.cpp"
 
  "control_system.h"
 "control_system.cpp"
 "mouse_raycast.h"
 "mouse_raycast.cpp"
 "character_control_system.h"
 "character_control_system.cpp"
 "agriculture_control_system.h"
 "agriculture_control_system.cpp"
 "trade_control_system.h"
 "trade_control_system.cpp"
 "machine_control_system.h"
 "machine_control_system.cpp"
 "deposit_control_system.h"
 "deposit_control_system.cpp"
)
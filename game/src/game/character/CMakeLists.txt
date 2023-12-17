cmake_minimum_required(VERSION 3.13)

project(characters)

target_sources(game PRIVATE
	"components.h"
	"character_system.h"
	"character_system.cpp"
	"../control/character_control_system.h"
	"../control/character_control_system.cpp"
)
cmake_minimum_required(VERSION 3.13)

project(machine_blueprint)

target_sources(game PRIVATE
	"machine_blueprint_creator.h"
	"machine_blueprint_creator.cpp"
	
	"blueprint_system.h"
	"blueprint_system.cpp"
)
cmake_minimum_required(VERSION 3.13)

project(machines_heater)

target_sources(game PRIVATE
	"components.h"
	"heater_system.h"
	"heater_system.cpp"
)
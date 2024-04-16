cmake_minimum_required(VERSION 3.13)

project(inventory)


target_sources(game PRIVATE
	"components.h"
	"inventory_system.h"
	"inventory_system.cpp"
)
cmake_minimum_required (VERSION 3.13)

project(game_tests_inventory)

target_sources(game_tests_project PRIVATE
	"inventory_system_tests.h"
	"inventory_system_tests.cpp"
)

cmake_minimum_required (VERSION 3.13)

project(game_tests)

add_subdirectory("inventory")

target_sources(game_tests_project PRIVATE
	"main.h"
	"main.cpp"
)
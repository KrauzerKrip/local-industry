cmake_minimum_required(VERSION 3.13)

project(machines_latex_extractor)

target_sources(game PRIVATE
	"components.h"
	"latex_extractor_system.h"
	"latex_extractor_system.cpp"
)
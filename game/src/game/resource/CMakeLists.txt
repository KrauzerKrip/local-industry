cmake_minimum_required(VERSION 3.13)

project(resource_)


target_sources(game PRIVATE
	"components.h"
	"internal_components.h"
	"deposit_extraction_system.h"
	"deposit_extraction_system.cpp"
	"deposit_task_system.h"
	"deposit_task_system.cpp"
	"deposit_system.h"
	"deposit_system.cpp"
)
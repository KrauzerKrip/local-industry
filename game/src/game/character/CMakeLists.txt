cmake_minimum_required(VERSION 3.28)

project(characters)

target_sources(game PRIVATE "components.h")

target_sources(game
  PRIVATE
	"task_queue.h"
	"task_queue.cpp"
	"character_task_system.h"
	"character_task_system.cpp"
	"character_system.h"
	"character_system.cpp"
)
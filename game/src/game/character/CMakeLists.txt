cmake_minimum_required(VERSION 3.28)

project(characters)

target_sources(game PRIVATE "components.h")

target_sources(game
  PRIVATE
    FILE_SET modules TYPE CXX_MODULES FILES
    "character.ixx"
	"character_system.ixx"
	"character_task_system.ixx"
	"task_queue.ixx"
)
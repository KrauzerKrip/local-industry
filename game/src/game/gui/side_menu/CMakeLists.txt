cmake_minimum_required(VERSION 3.13)

project(gui_side_menu)

target_sources(game PRIVATE
	"side_menu.h"
	"side_menu.cpp"
	"buttons/task_menu_button.h"
	"buttons/task_menu_button.cpp"
	"task_menu/task_menu.h"
	"task_menu/task_menu.cpp"
	"task_menu/task_list.h"
	"task_menu/task_list.cpp"
	"task_menu/task_list_layout.h"
	"task_menu/task_list_layout.cpp"
	"task_menu/character_task_list_controller.h"
	"task_menu/character_task_list_controller.cpp"
	"task_menu/planned_task_list_controller.h"
	"task_menu/planned_task_list_controller.cpp"
	"task_menu/task_view.h"
	"task_menu/task_view.cpp"
	"task_menu/task_list_controller.h"
	
)
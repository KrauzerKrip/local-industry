cmake_minimum_required(VERSION 3.13)

project(gui_dependencies_fabric)

target_sources(game PRIVATE
	"gui_dependencies_fabric.h"
	"openGL/gl_gui_dependencies_fabric.h"
	"openGL/gl_gui_dependencies_fabric.cpp"
)
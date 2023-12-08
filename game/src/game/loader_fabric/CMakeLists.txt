cmake_minimum_required(VERSION 3.13)

project(loader_fabric)

target_sources(game PRIVATE
	"loader_fabric.h"
	"openGL/gl_loader_fabric.h"
	"openGL/gl_loader_fabric.cpp"
)
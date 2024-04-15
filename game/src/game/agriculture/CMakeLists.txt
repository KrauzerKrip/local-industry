cmake_minimum_required(VERSION 3.13)

project(agriculture)


target_sources(game PRIVATE
	"components.h"
	"agriculture_system.h"
	"agriculture_system.cpp"
)
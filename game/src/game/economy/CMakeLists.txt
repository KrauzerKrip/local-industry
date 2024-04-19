cmake_minimum_required(VERSION 3.13)

project(economy)

target_sources(game PRIVATE
	"components.h"
	"trade_system.h"
	"trade_system.cpp"
)
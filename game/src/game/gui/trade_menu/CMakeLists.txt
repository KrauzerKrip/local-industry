cmake_minimum_required(VERSION 3.13)

project(trade_menu)

target_sources(game PRIVATE
	"trade_menu_view.h"
	"trade_menu_view.cpp"
	"trade_menu_controller.h"
	"trade_menu_controller.cpp"
	"trade_menu_slot.h"
	"trade_menu_slot.cpp"
)
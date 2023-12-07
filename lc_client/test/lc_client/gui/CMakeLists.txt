cmake_minimum_required (VERSION 3.13)

project(lc_client_test_gui)

target_sources(test_project PRIVATE
	"layout_controller_test.h"
	"layout_controller_test.cpp"
	"vbox_test.h"
 "vbox_test.cpp")
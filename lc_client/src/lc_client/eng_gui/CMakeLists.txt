cmake_minimum_required (VERSION 3.13)

project(eng_gui)

add_subdirectory("layout")
add_subdirectory("widgets")

target_sources(lc_client 
    PRIVATE
    "gui_console.h"
    "gui_console.cpp"

    "gui.h"
    "gui.cpp"
    "view/text_presenter.h"
    "paint_objects/text.h"
    "paint_objects/text.cpp"
    "controller/text_controller.h"
     "controller/i_text_controller.h"
    
     "paint_objects/background.h"
 "paint_objects/background.cpp"
    "paint_objects/image_background.cpp"
    "paint_objects/image_background.cpp"
)
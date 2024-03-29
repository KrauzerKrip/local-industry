cmake_minimum_required (VERSION 3.13)

project(eng_gui)

add_subdirectory("layout")
add_subdirectory("widgets")

target_sources(lc_client 
    PRIVATE
    "includes.h"

    "gui_console.h"
    "gui_console.cpp"

    "gui.h"
    "gui.cpp"
    
    "view/gui_presenter.h"
    "view/gui_presenter.cpp"

    "input/input_receiver.h"   
    "input/events.h"
     "input/input_controller.h"
     "input/input_controller.cpp"
     
    
     "paint_objects/background.h"
 
    "paint_objects/image_background.cpp"
    "paint_objects/image_background.cpp"
    "paint_objects/color_background.h"
    "paint_objects/color_background.cpp"
    "paint_objects/blur_background.h"
    "paint_objects/blur_background.cpp"
    "paint_objects/text.h"

)
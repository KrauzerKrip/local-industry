cmake_minimum_required (VERSION 3.13)

project(eng_gui_widgets)

target_sources(lc_client 
    PRIVATE
    "widget.h"
    "widget.cpp"
    "text_widget.h"
    "text_widget.cpp"
    "button.h"
    "button.cpp"
    "rectangle.h"
    "rectangle.cpp"
    "layer.h"
    "layer.cpp"
    "dependencies.h"
   )
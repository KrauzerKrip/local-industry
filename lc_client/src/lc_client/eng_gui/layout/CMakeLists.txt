cmake_minimum_required (VERSION 3.13)

project(eng_gui_layout)

target_sources(lc_client 
    PRIVATE
  "layout_controller.h" "layout_controller.cpp"
 "layouts/frame.h" "layouts/frame.cpp"
 "layouts/layout.h"
)
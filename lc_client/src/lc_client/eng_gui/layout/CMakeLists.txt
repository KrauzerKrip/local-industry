cmake_minimum_required (VERSION 3.13)

project(eng_gui_layout)

target_sources(lc_client 
    PRIVATE
    "modes.h"
    "layouts/layouts.h"
  "layout_controller.h" "layout_controller.cpp"
 "layouts/frame.h" "layouts/frame.cpp"
 "layouts/layout.h" "widget_data.h" "layout_data.h"
 "layouts/vbox.h"
 "layouts/vbox.cpp"
 "layouts/layout.cpp"
 "layouts/grid.h"
 "layouts/grid.cpp"
 "layouts/anchor_pane.h"
 "layouts/anchor_pane.cpp"
  "layouts/percentage_pane.h"
 "layouts/percentage_pane.cpp"
 "layouts/hbox.h"
 "layouts/hbox.cpp"
 "layouts/vertical_scroll_area.h"
 "layouts/vertical_scroll_area.cpp"
 
 
 
)
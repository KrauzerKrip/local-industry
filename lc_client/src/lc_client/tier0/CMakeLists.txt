cmake_minimum_required (VERSION 3.13)

project(eng_procedures)

target_sources(lc_client 
    PRIVATE
        "conpar/conpar.h"
        "conpar/conpar.cpp"
        "conpar/parameters.h"
        "conpar/parameters.cpp"
        "conpar/conpars_init.h"
        "conpar/conpars_init.cpp"
        "tier0.h"
        "tier0.cpp"

        "console/i_console.h"
        "console/i_console_input.h"
        "console/console.h"
        "console/console.cpp"
        "console/command_parser.h"
        "console/command_parser.cpp"
        "console/command.h"
        "console/command.cpp"

        "imgui_fonts.h"
)
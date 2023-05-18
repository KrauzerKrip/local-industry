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
)
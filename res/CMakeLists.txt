cmake_minimum_required (VERSION 3.13)

project(res)

find_package(CMakeRC CONFIG REQUIRED)
cmrc_add_resource_library(eng_resources ALIAS eng::rc "dev/shaders/base.frag" "dev/shaders/base.vert")
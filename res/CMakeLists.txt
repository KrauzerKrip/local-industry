cmake_minimum_required (VERSION 3.13)

project(res)

find_package(CMakeRC CONFIG REQUIRED)
cmrc_add_resource_library(eng_resources ALIAS eng::rc "dev/shaders/frag/base.frag" "dev/shaders/vert/base.vert")
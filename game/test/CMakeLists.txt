cmake_minimum_required (VERSION 3.13)

project(game_tests_project)

include(CTest) 
#include(GoogleTest)

add_executable(game_tests_project)

enable_testing()

add_test(
  NAME game_tests_name
  COMMAND $<TARGET_FILE:game_tests_project>
  )


target_include_directories(game_tests_project PRIVATE game)
target_link_libraries(game_tests_project PRIVATE game)

add_subdirectory("game")

find_package(GTest CONFIG REQUIRED)
target_link_libraries(game_tests_project PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main )

#gtest_discover_tests(game_tests_project)

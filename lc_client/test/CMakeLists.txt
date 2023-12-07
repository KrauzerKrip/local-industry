cmake_minimum_required (VERSION 3.13)

project(test_project)

include(CTest) 

enable_testing()

add_executable(test_project)

target_include_directories(test_project PRIVATE lc_client)
target_link_libraries(test_project PRIVATE lc_client)

add_subdirectory("lc_client")

find_package(GTest CONFIG REQUIRED)
target_link_libraries(test_project PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(
  NAME test_project
  COMMAND $<TARGET_FILE:test_project>
  )

#GTEST_ADD_TESTS( lc_client_test
 #lc_client_test)

#add_test(NAME test_project COMMAND test_project WORKING_DIRECTORY ${UNIT_TEST_BIN_OUTPUT_DIR})
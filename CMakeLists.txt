cmake_minimum_required(VERSION 3.10)
project(104WeekCMastery)

#Include CTest for running tests 
include(CTest)

#Add your production code as a library
add_library(Simple STATIC src/simple.c)

#Add Unity from the submodule
add_library(Unity STATIC external/unity/src/unity.c)
target_include_directories(Unity PUBLIC external/unity/src)

#Add test executable
add_executable(SimpleTest test/test_simple.c)
target_link_libraries(SimpleTest Simple Unity)

#Add test executable
add_executable(ReverseTest test/week01/test_reverse.c)
target_link_libraries(ReverseTest Reverse Unity)

#Register the test with CTest
add_test(NAME SimpleTest COMMAND SimpleTest)


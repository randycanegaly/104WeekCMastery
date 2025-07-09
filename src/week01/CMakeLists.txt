cmake_minimum_required(VERSION 3.10)
project(week01)

#Include CTest for running tests 
include(CTest)

#Add your production code as a library
add_library(Vector STATIC vector.c)

#Add your production code as a library
add_library(Calc STATIC ptr_calc.c)

#Add Unity from the submodule
add_library(Unity STATIC ../../external/unity/src/unity.c)
target_include_directories(Unity PUBLIC ../../external/unity/src)

#Add test executables
add_executable(VectorTest ../../test/week01/test_vector.c)
target_link_libraries(VectorTest Vector Unity)

add_executable(CalcTest ../../test/week01/test_calc.c)
target_link_libraries(CalcTest Calc Unity)

#Register the tests with CTest
add_test(NAME VectorTest COMMAND VectorTest)
add_test(NAME CalcTest COMMAND CalcTest)


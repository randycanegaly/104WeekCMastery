#include "../../external/unity/src/unity.h"
#include "../../src/week01/ptr_calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setUp(void) {}

void tearDown(void) {}

void test_add(void) {
  int sum = add(3, 6);
  TEST_ASSERT_EQUAL_INT(9, sum);
}

void test_ptr_add(void) {
  int result = calculate_two_ops(add, 3, 6);
  TEST_ASSERT_EQUAL_INT(9, result);
}

void test_ptr_sub(void) {
  int result = calculate_two_ops(sub, 6, 3);
  TEST_ASSERT_EQUAL_INT(3, result);
}

void test_ptr_mult(void) {
  int result = calculate_two_ops(mult, 6, 3);
  TEST_ASSERT_EQUAL_INT(18, result);
}

void test_ptr_div(void) {
  int result = calculate_two_ops(mydiv, 6, 3);
  TEST_ASSERT_EQUAL_INT(2, result);
}

void test_ptr_div_by_zero(void) {
  int result = calculate_two_ops(mydiv, 6, 0);
  TEST_ASSERT_EQUAL_INT(2, result);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_add);
  RUN_TEST(test_ptr_add);
  RUN_TEST(test_ptr_sub);
  RUN_TEST(test_ptr_mult);
  RUN_TEST(test_ptr_div);
  RUN_TEST(test_ptr_div_by_zero);
  return UNITY_END();
}

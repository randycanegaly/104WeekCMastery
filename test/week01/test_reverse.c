#include "../../external/unity/src/unity.h"
#include "../../src/week01/reverse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str0;
char *str1;
char *str2;
char *str3;
int strlength;

void setUp(void) {
  str0 = NULL;

  strlength = strlen(" ");
  str1 = (char *)malloc(sizeof(char) * strlength + 1);
  strcpy(str1, " ");

  strlength = strlen("seven");
  str3 = (char *)malloc(sizeof(char) * strlength + 1);
  strcpy(str3, "seven");

  strlength = strlen("Canegaly");
  str2 = (char *)malloc(sizeof(char) * strlength + 1);
  strcpy(str2, "Canegaly");
}

void tearDown(void) {}

void test_swap() {
  swap(str2, str2 + strlength - 1);
  TEST_ASSERT_EQUAL_CHAR('y', *str2);
  TEST_ASSERT_EQUAL_CHAR('C', *(str2 + strlength - 1));
}

void test_reverse_NULL_string() {
  reverse(str0);
  TEST_ASSERT_NULL(str0);
}

void test_reverse_empty_string() {
  reverse(str1);
  TEST_ASSERT_EQUAL_STRING(" ", str1);
}

void test_reverse() {
  reverse(str2);
  TEST_ASSERT_EQUAL_STRING("ylagenaC", str2);
}

void test_reverse_odd_string() {
  reverse(str3);
  TEST_ASSERT_EQUAL_STRING("neves", str3);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_swap);
  RUN_TEST(test_reverse);
  RUN_TEST(test_reverse_NULL_string);
  RUN_TEST(test_reverse_empty_string);
  RUN_TEST(test_reverse_odd_string);
  return UNITY_END();
}

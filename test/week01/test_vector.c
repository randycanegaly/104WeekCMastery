#include "../../external/unity/src/unity.h"
#include "../../src/week01/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DynArray *array; // Global pointer

void setUp(void) {
  array = malloc(sizeof(DynArray));
  if (array == NULL) {
    TEST_FAIL_MESSAGE("Failed to allocate memory for array");
  }
  init(array);
  if (array->buffer == NULL) {
    free(array);
    array = NULL;
    TEST_FAIL_MESSAGE("Failed to allocate memory for array->buffer in init");
  }
}

void tearDown(void) {
  if (array) {
    if (array->buffer) {
      free(array->buffer);
      array->buffer = NULL;
    }
    free(array);
    array = NULL;
  }
}

void test_init_vector(void) {
  TEST_ASSERT_EQUAL_INT(0, array->count);
  TEST_ASSERT_EQUAL_INT(BASE_SIZE, array->capacity);
}

void test_available_space(void) {
  int space = available(array);
  TEST_ASSERT_EQUAL_INT(BASE_SIZE, space); // BASE_SIZE chars available
}

void test_resize_new_vector_equal(void) {
  resize(array);
  TEST_ASSERT_NOT_NULL(array->buffer); // Ensure resize didn't fail
  TEST_ASSERT_EQUAL_INT(BASE_SIZE * 2, array->capacity); // Doubled capacity
}

void test_append_string(void) {
  char *str = "hello";
  append(array, str);
  printf("test_append_string: count = %d, capacity = %d, buffer = ",
         array->count, array->capacity);
  for (int i = 0; i < array->count; i++) {
    printf("%c", array->buffer[i]);
  }
  printf("\n");
  TEST_ASSERT_EQUAL_INT(5, array->count);            // "hello" has 5 chars
  TEST_ASSERT_EQUAL_INT(BASE_SIZE, array->capacity); // No resize needed
  TEST_ASSERT_EQUAL_STRING("hello", array->buffer);  // Compare buffer contents
}

void test_append_string_needs_resize(void) {
  char *str = "abcdefghijk"; // 11 chars, needs resize (8 < 11)
  append(array, str);
  printf(
      "test_append_string_needs_resize: count = %d, capacity = %d, buffer = ",
      array->count, array->capacity);
  for (int i = 0; i < array->count; i++) {
    printf("%c", array->buffer[i]);
  }
  printf("\n");
  TEST_ASSERT_EQUAL_INT(11, array->count);
  TEST_ASSERT_EQUAL_INT(BASE_SIZE * 2, array->capacity); // Resized to 16
  TEST_ASSERT_EQUAL_STRING("abcdefghijk", array->buffer);
}

void test_append_twice(void) {
  char *str = "abcdefghijk"; // 11 chars, needs resize (8 < 11)
  append(array, str);
  char *str2 = "lmnopqrstuvwxyz";
  append(array, str2);
  for (int i = 0; i < array->count; i++) {
    printf("%c", array->buffer[i]);
  }
  printf("\n");
  printf("capacity: %d\n", array->capacity);
  TEST_ASSERT_EQUAL_INT(26, array->count);
  TEST_ASSERT_EQUAL_INT(BASE_SIZE * 4, array->capacity); // Resized to 16
  TEST_ASSERT_EQUAL_STRING("abcdefghijklmnopqrstuvwxyz", array->buffer);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init_vector);
  RUN_TEST(test_available_space);
  RUN_TEST(test_resize_new_vector_equal);
  RUN_TEST(test_append_string);
  RUN_TEST(test_append_string_needs_resize);
  RUN_TEST(test_append_twice);
  return UNITY_END();
}

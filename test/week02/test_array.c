#include "../../external/unity/src/unity.h"
#include "../../src/week02/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 2
#define COLS 2
#define FILL 'q'

Darray *darray;

void setUp(void) { darray = init(ROWS, COLS); }

void tearDown(void) {}

void test_init() {
  TEST_ASSERT_NOT_NULL(darray);
  TEST_ASSERT_EQUAL_INT(ROWS, darray->rows);
  TEST_ASSERT_EQUAL_INT(COLS, darray->cols);
}

void test_fill() {
  fill(darray, ROWS, COLS, FILL);
  for (int i = 0; i < ROWS; i++) {
    char *row = *darray->array;
    for (int j = 0; j < COLS; j++) {
      TEST_ASSERT_EQUAL_CHAR(FILL, *(row + j));
    }
  }
}

void test_resize() {
  int new_rows = ROWS * 2;
  int new_cols = COLS * 2;

  fill(darray, ROWS, COLS, FILL);
  resize(darray, new_rows, new_cols);
  for (int i = 0; i < new_rows; i++) {
    for (int j = 0; j < new_cols; j++) {
      printf("at row: %d, col: %d, value: %c\n", i, j, darray->array[i][j]);
    }
  }

  TEST_ASSERT_EQUAL_INT(ROWS * 3, darray->rows);
  TEST_ASSERT_EQUAL_INT(COLS * 3, darray->cols);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init);
  RUN_TEST(test_fill);
  RUN_TEST(test_resize);
  return UNITY_END();
}

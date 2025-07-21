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

void tearDown(void) {
  if (darray != NULL) {
    if (darray->array != NULL) {
      for (int i = 0; i < darray->rows; i++) {
        if (*(darray->array + i) != NULL) {
          free(*(darray->array + i));
        }
      }
    }
    free(darray->array);
    darray->array = NULL;
    darray = NULL;
  }
}

void test_init() {
  TEST_ASSERT_NOT_NULL(darray);
  TEST_ASSERT_EQUAL_INT(ROWS, darray->rows);
  TEST_ASSERT_EQUAL_INT(COLS, darray->cols);
}

void test_fill() {
  fill(darray, FILL);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // printf("at row: %d, col: %d, value: %c\n", i, j, darray->array[i][j]);
      TEST_ASSERT_EQUAL_CHAR('q', darray->array[i][j]);
    }
  }
}

void test_resize() {
  int new_rows = ROWS * 2;
  int new_cols = COLS * 2;

  fill(darray, FILL);
  resize(darray, new_rows, new_cols);
  for (int i = 0; i < new_rows; i++) {
    for (int j = 0; j < new_cols; j++) {
      // printf("at row: %d, col: %d, value: %c\n", i, j, darray->array[i][j]);
    }
  }

  TEST_ASSERT_EQUAL_INT(ROWS * 2, darray->rows);
  TEST_ASSERT_EQUAL_INT(COLS * 2, darray->cols);
}

void test_free() {
  fill(darray, FILL);
  dfree(darray);
  TEST_ASSERT_NULL(darray->array);
}

void test_dset() {
  char rownum = 2;
  char colnum = 2;

  fill(darray, FILL);
  dset(darray, rownum, colnum, 'k');
  TEST_ASSERT_EQUAL_CHAR('k', darray->array[1][1]);
}

void test_dget() {
  char rownum = 2;
  char colnum = 2;

  fill(darray, FILL);
  char result;
  dset(darray, rownum, colnum, 'm');
  dget(darray, rownum, colnum, &result);
  TEST_ASSERT_EQUAL_CHAR('m', darray->array[1][1]);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init);
  RUN_TEST(test_fill);
  RUN_TEST(test_resize);
  RUN_TEST(test_free);
  RUN_TEST(test_dset);
  RUN_TEST(test_dget);
  return UNITY_END();
}

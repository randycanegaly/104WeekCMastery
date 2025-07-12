#include "../../external/unity/src/unity.h"
#include "../../src/week02/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 2
#define COLS 2
#define FILL 'q'

void setUp(void) {}

void tearDown(void) {}

void test_init() {
  char **result = init(ROWS, COLS);
  TEST_ASSERT_NOT_NULL(result);
}

void test_fill() {
  char **result = init(ROWS, COLS);
  TEST_ASSERT_NOT_NULL(result);
  fill(result, ROWS, COLS, FILL);
  TEST_ASSERT_EQUAL_CHAR(FILL, **result);
  for (int i = 0; i < ROWS; i++) {
    printf("%c\n", *(*result + i));
    TEST_ASSERT_EQUAL_CHAR('q', *(*result + i));
    //*result points to the first char of the row. *result + i moves
    // along the row. *(*result + i) gets the char value there
  }
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_init);
  RUN_TEST(test_fill);
  return UNITY_END();
}

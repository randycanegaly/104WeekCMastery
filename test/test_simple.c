#include "../external/unity/src/unity.h"
#include "../src/simple.h"

void setUp(void) {}
void tearDown(void) {}

void test_Add_Simple(void) { TEST_ASSERT_EQUAL_INT(5, Add(2, 3)); }

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_Add_Simple);
  return UNITY_END();
}

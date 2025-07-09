#include <stdio.h>
#include <stdlib.h>

#include "ptr_calc.h"

int add(int a, int b) { return a + b; }

int calculate_two_ops(fptr_calc_two operation, int a, int b) {
  int result = operation(a, b);
  return result;
}

int sub(int a, int b) { return a - b; }
int mult(int a, int b) { return a * b; }
int mydiv(int a, int b) {
  if (b != 0) {
    return a / b;
  } else {
    printf("DIVIDE BY ZERO!!!\n");
    exit(1);
  }
}
int square(int a) { return a * a; }
float sq_root(int a);

float calculate_one_ops(fptr_calc_one operation, int a) {
  float result = (float)operation(a);
  return result;
}

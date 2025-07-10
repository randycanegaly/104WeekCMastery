#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ptr_calc.h"

int add(int a, int b) { return a + b; }
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

double sq_root(double a) { return sqrt(a); }

int calculate_two_ops(fptr_calc_two operation, int a, int b) {
  int result = operation(a, b);
  return result;
}

int calculate_one_int(fptr_calc_one_int operation, int a) {
  float result = (float)operation(a);
  return result;
}

double calculate_one_double(fptr_calc_one_double operation, double a) {
  double result = operation(a);
  return result;
}

#ifdef IS_EXE
int main(int argc, char **argv) {
  int op;
  if (argc == 4) {
    op = *(++argv)[0];
    int first = atoi((*(++argv)));
    int second = atoi((*(++argv)));

    switch (op) {
    case '+':
      printf("result: %d\n", calculate_two_ops(add, first, second));
      break;
    case '-':
      printf("result: %d\n", calculate_two_ops(sub, first, second));
      break;
    case 'x':
      printf("result: %d\n", calculate_two_ops(mult, first, second));
      break;
    case '/':
      printf("result: %d\n", calculate_two_ops(mydiv, first, second));
      break;
    }
  } else if (argc == 3) {
    op = *(++argv)[0];
    int operand = atoi((*(++argv)));

    switch (op) {
    case 's':
      printf("result: %d\n", calculate_one_int(square, operand));
      break;
    case 'r':
      printf("result: %f\n", calculate_one_double(sq_root, operand));
      break;
    }
  } else {
    printf("Usage: Enter an operation, then one or two operands\n");
  }

  return EXIT_SUCCESS;
}
#endif /* ifdef MACRO */

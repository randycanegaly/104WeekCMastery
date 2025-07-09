#ifndef PTR_CALC_H
#define PTR_CALC_H

typedef int (*fptr_calc_two)(int, int);
typedef int (*fptr_calc_one)(int);

int add(int a, int b);
int sub(int a, int b);
int mult(int a, int b);
int mydiv(int a, int b);
int square(int a);
float sq_root(int a);

int calculate_two_ops(fptr_calc_two operation, int a, int b);
float calculate_one_ops(fptr_calc_one operation, int a);
#endif

#ifndef PTR_CALC_H
#define PTR_CALC_H

typedef int (*fptr_calc_two)(int, int);
typedef int (*fptr_calc_one_int)(int);
typedef double (*fptr_calc_one_double)(double);

int add(int a, int b);
int sub(int a, int b);
int mult(int a, int b);
int mydiv(int a, int b);
int square(int a);
double sq_root(double a);

int calculate_two_ops(fptr_calc_two operation, int a, int b);
int calculate_one_int(fptr_calc_one_int operation, int a);
double calculate_one_double(fptr_calc_one_double operation, double a);
#endif

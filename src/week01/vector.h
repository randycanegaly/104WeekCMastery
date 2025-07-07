#ifndef VECTOR_H
#define VECTOR_H

#define BASE_SIZE 8

typedef struct {
  char *buffer;
  char *nextPosition;
  int capacity;
  int count;
} DynArray;

void init(DynArray *arr);
int available(DynArray *arr);
void resize(DynArray *array);
void append(DynArray *array, char *str);

#endif

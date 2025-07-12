#include <stdlib.h>
#include <string.h>

#include "array.h"

DynArray *init(int rows, int cols) {
  static DynArray arr;

  char **arr = (char **)malloc(sizeof(char *) * rows);
  if (arr == NULL)
    return NULL;

  for (int i = 0; i < rows; i++) {
    *(arr + i) = (char *)calloc(cols, sizeof(char));
    if (*(arr + i) == NULL)
      return NULL;
  }

  return arr;
}

void fill(char **arr, int rows, int cols, char fill) {
  char *temp;
  for (int i = 0; i < rows; i++) {
    temp = *(arr + i);
    for (int j = 0; j < cols; j++) {
      *(temp + j) = fill;
    }
  }
}

#ifdef IS_EXE
int main(void) {}
#endif /* ifdef IS_EXE */

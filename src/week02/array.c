#include <stdlib.h>
#include <string.h>

#include "array.h"

Darray *init(int rows, int cols) {
  static Darray darray;

  darray.array = (char **)malloc(sizeof(char *) * rows);
  if (darray.array == NULL)
    return NULL;

  for (int i = 0; i < rows; i++) {
    *(darray.array + i) = (char *)calloc(cols, sizeof(char));
    if (*(darray.array + i) == NULL)
      return NULL;
  }

  darray.rows = rows;
  darray.cols = cols;

  return &darray;
}

void fill(Darray *darray, int rows, int cols, char fill) {
  char *temp;
  for (int i = 0; i < rows; i++) {
    temp = *(darray->array + i);
    for (int j = 0; j < cols; j++) {
      *(temp + j) = fill;
    }
  }
}

void resize(Darray *darray, int new_rows, int new_cols) {
  char **resized = realloc(darray->array, sizeof(char) * new_rows);
  if (resized == NULL)
    free(darray->array);

  darray->array = resized;

  darray->rows = new_rows;
  darray->cols = new_cols;
}

#ifdef IS_EXE
int main(void) {
  Darray *darray = init(2, 2);
  fill(darray, 2, 2, 'x');
  resize(darray, 4, 4);
}
#endif /* ifdef IS_EXE */

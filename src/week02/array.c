#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

Darray *init(int rows, int cols) {
  Darray *darray = (Darray *)malloc(sizeof(Darray));

  darray->array = (char **)malloc(sizeof(char *) * rows);
  if (darray == NULL)
    return NULL;

  for (int i = 0; i < rows; i++) {
    *(darray->array + i) = (char *)calloc(cols, sizeof(char));
    if (*(darray->array + i) == NULL) {
      // Clean up any rows that previously calloced correctly
      for (int j = 0; j < i; j++) {
        free(*(darray->array + j)); // free prior rows
      }
      free(darray->array); // free the memory for the array of pointers to rows
      free(darray);        // free the allocated memory for the Darray
      return NULL; // all memory cleanup done - retrun NULL to indicate failure
    }
  }
  darray->rows = rows;
  darray->cols = cols;
  return darray;
}

void fill(Darray *darray, char fill) {
  // char *temp;
  for (int i = 0; i < darray->rows; i++) {
    // temp = (*(darray->array + i));
    for (int j = 0; j < darray->cols; j++) {
      // darray->array[i][j] = fill;
      //*(temp + j) = fill;
      //*(darray->array + i) is the same as darray->array[i]
      //*((*(darray->array + i)) + j) is the same as darray->array[i][j]

      *((*(darray->array + i)) + j) = fill;
    }
  }
}

void resize(Darray *darray, int new_rows, int new_cols) {
  // 1. Reallocate memory for the new size (new_rows) of
  // the array of char* pointers (each points to the front of the row of chars)
  char **temp_array = realloc(darray->array, sizeof(char *) * new_rows);
  if (temp_array == NULL) {
    // Handle error: realloc failed. All bets are off.
    fprintf(stderr, "Error: Failed to reallocate rows array for Darray.\n");
    return;
  }
  darray->array = temp_array;

  // 2. Walk the new length of the array of row pointers
  // and reallocate memory for the new length (new_cols) for each row
  // Cases:
  // A. More rows - allocate additional rows and initialize them
  // B. Fewer rows - free the extra rows
  // C. New row length, reallocate the row to the new size
  // A
  if (new_rows > darray->rows) {
    // New rows added. Allocate memory for them
    for (int i = darray->rows; i < new_rows; i++) {
      *(darray->array + i) = (char *)calloc(new_cols, sizeof(char));
      if (*(darray->array + i) == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new row.\n");
        return;
      }
    }
  } else if (new_rows < darray->rows) { // B
    // Rows removed, free the excess rows
    for (int i = new_rows; i < darray->rows; i++) {
      free(*(darray->array + i));
      *(darray->array + i) = NULL;
    }
  }

  // Adjust (reallocate??) all rows to the new column number
  // some of these may have already been done above but
  // doing them again won't have any effect
  for (int i = 0; i < new_rows; i++) {
    char *temp_row =
        (char *)realloc(*(darray->array + i), new_cols * sizeof(char));
    if (temp_row == NULL) {
      // Handle error: realloc failed. All bets are off.
      fprintf(stderr, "Error: Failed to reallocate new row.\n");
      return;
    }
    *(darray->array + i) = temp_row;

    // May have made row longer, realloc did not initialize new column elements
    // fill them
    if (new_cols > darray->cols) {
      memset(*(darray->array) + darray->cols, 0, new_cols - darray->cols);
    }
  }

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

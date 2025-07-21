#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

Darray *init(int rows, int cols) {
  Darray *darray = (Darray *)malloc(sizeof(Darray));
  if (darray == NULL)
    return NULL;

  darray->array = (char **)malloc(sizeof(char *) * rows);
  if (darray == NULL) {
    free(darray);
    return NULL;
  }

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
  // resizes the array of char*s
  char **temp_array = realloc(darray->array, sizeof(char *) * new_rows);
  if (temp_array == NULL) {
    fprintf(stderr, "Error: Failed to reallocate rows array for Darray.\n");
    return;
  }
  darray->array = temp_array;

  // allocate for columns for existing rows
  for (int i = 0; i < (new_rows < darray->rows ? new_rows : darray->rows);
       i++) {
    char *temp_row = realloc(*(darray->array + i), new_cols * sizeof(char));
    if (temp_row == NULL) {
      fprintf(stderr, "Error: Failed to reallocate row %d.\n", i);
      // Consider a more robust error recovery here, like attempting to free
      // already reallocated rows and reverting to original state, or aborting.
      return;
    }
    *(darray->array + i) = temp_row;

    // for more columns case, memset added row elements
    if (new_cols > darray->cols) {
      // Only memset if columns are added and for existing data
      memset(*(darray->array + i) + darray->cols, 0, new_cols - darray->cols);
    }
  }

  // allocate for columns in new rows
  if (new_rows > darray->rows) {
    for (int i = darray->rows; i < new_rows; i++) {
      *(darray->array + i) =
          calloc(new_cols, sizeof(char)); // calloc initializes to zero
      if (*(darray->array + i) == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new row %d.\n",
                i);
        // Important: Clean up partial allocations before returning!
        // This cleanup for resize is much more complex than init.
        // For simplicity, for now, we'll just return.
        return;
      }
    }
  } else if (new_rows < darray->rows) { // free up "cut off" rows
    for (int i = new_rows; i < darray->rows; i++) {
      free(*(darray->array + i));
      *(darray->array + i) = NULL; // Set to NULL after freeing
    }
  }

  darray->rows = new_rows;
  darray->cols = new_cols;
}

void dset(Darray *darray, int row, int col, char val) {
  if (darray == NULL || row > darray->rows || col > darray->cols) {
    fprintf(stderr, "Trying to set beyond the bounds of the 2D array.\n");
    return;
  }

  char **temp_row;
  char *temp_col;
  for (int i = 0; i < darray->rows; i++) {
    temp_row = darray->array + i;
  }
  if (temp_row == NULL) {
    fprintf(stderr, "In dset(), setting to NULL row pointer.\n");
    return;
  }

  for (int j = 0; j < darray->cols; j++) {
    temp_col = (*temp_row) + j;
  }
  if (temp_col == NULL) {
    fprintf(stderr, "In dset(), setting to NULL col pointer.\n");
    return;
  }

  *temp_col = val;
}

void dget(Darray *darray, int row, int col, char *val) {
  if (darray == NULL || row > darray->rows || col > darray->cols) {
    fprintf(stderr, "Trying to get beyond the bounds of the 2D array.\n");
    return;
  }

  char **temp_row;
  char *temp_col;
  for (int i = 0; i < darray->rows; i++) {
    temp_row = darray->array + i;
  }
  if (temp_row == NULL) {
    fprintf(stderr, "In dget(), getting from NULL row pointer.\n");
    return;
  }

  for (int j = 0; j < darray->cols; j++) {
    temp_col = (*temp_row) + j;
  }
  if (temp_col == NULL) {
    fprintf(stderr, "In dget(), getting from NULL col pointer.\n");
    return;
  }

  *val = *temp_col;
}

/*
 * free all resources under the Darray
 */
void dfree(Darray *darray) {
  if (darray != NULL) {
    if (darray->array != NULL) {
      for (int i = 0; i < darray->rows; i++) {
        if (*(darray->array + i) != NULL) {
          free(*(darray->array + i));
        }
      }
    }
    free(darray->array);
    darray->array = NULL;
  }
}

#ifdef IS_EXE
int main(void) {
  Darray *darray = init(2, 2);
  fill(darray, 2, 2, 'x');
  resize(darray, 4, 4);
  dfree(darray);
}
#endif /* ifdef IS_EXE */

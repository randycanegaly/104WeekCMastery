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
  /*
   Cases:
   1. more rows, columns same
   2. fewer rows, columns same
   3. more rows, columns fewer
   4. more rows, columns more
   5. fewer rows, columns fewer
   6. fewer rows, columns more
  */

  /*
  Cases 1 and 2
  These next lines grow or shrink the array of char pointers as needed
  */
  char **temp_array = realloc(darray->array, sizeof(char *) * new_rows);
  if (temp_array == NULL) {
    // Handle error: realloc failed. All bets are off.
    fprintf(stderr, "Error: Failed to reallocate rows array for Darray.\n");
    return;
  }
  darray->array = temp_array;

  // Case 1
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

  /*Note: Cases 1 and 2 already took care of more rows vs. fewer rows.
  So that cases 3 through 6 now consolidate to two cases:
  A. more columns
  B. fewer columns
  */

  // Case A
  //  Adjust (reallocate??) all rows to the new column number
  //  some of these may have already been done above but
  //  doing them again won't have any effect
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
      memset(*(darray->array + i) + darray->cols, 0, new_cols - darray->cols);
    }
  }

  darray->rows = new_rows;
  darray->cols = new_cols;
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

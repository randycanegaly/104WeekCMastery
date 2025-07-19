typedef struct {
  int rows;
  int cols;
  char **array;
} Darray;

Darray *init(int rows, int cols);
void fill(Darray *darray, char fill);
void resize(Darray *darray, int new_rows, int new_cols);

typedef struct {
  int rows;
  int cols;
  char **array;
} Darray;

Darray *init(int rows, int cols);
void fill(Darray *darray, char fill);
void resize(Darray *darray, int new_rows, int new_cols);
void dfree(Darray *darray);
void dset(Darray *darray, int row, int col, char val);
void dget(Darray *darray, int row, int col, char *val);

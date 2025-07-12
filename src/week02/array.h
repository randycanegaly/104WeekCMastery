typedef struct {
  int rows;
  int cols;
  char **array;
} DynArray;

DynArray *init(int rows, int cols);
void fill(char **arr, int rows, int cols, char fill);

#include <memory.h>
#include <stdbool.h>
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

void init(DynArray *arr) {
  arr->buffer = (char *)malloc(BASE_SIZE * sizeof(int));
  arr->nextPosition =
      arr->buffer; // TO DO - Do I need this? Take nextPosition and use count?
  arr->capacity = BASE_SIZE;
  arr->count = 0;
}

int available(DynArray *arr) {
  int available = (arr->buffer + arr->capacity - arr->nextPosition);
  return available;
}

void resize(DynArray *array) {
  if (array == NULL || array->buffer == NULL)
    return;
  int new_capacity = array->capacity * 2;
  // realloc preserves data in the reallocated memory block
  // the resized memory allocation
  char *new_buffer = realloc(array->buffer, new_capacity);
  if (new_buffer == NULL) {
    // Handle realloc failure (keep original buffer)
    return;
  }
  array->buffer = new_buffer;
  array->capacity = new_capacity;
}

void append(DynArray *array, char *str) {
  if (array == NULL || array->buffer == NULL || str == NULL)
    return;

  size_t str_len =
      strlen(str); // Number of chars to append (excluding null terminator)

  // Resize if needed until capacity is sufficient
  while (array->capacity - array->count < str_len) {
    resize(array);
    if (array->buffer == NULL)
      return; // Resize failed
  }

  // Copy str to the end of buffer
  memcpy(array->buffer + array->count, str, str_len);
  array->count += str_len; // Update count
  array->nextPosition = array->nextPosition + array->count;
}

/*int main(int argc, char *argv[]) {
  DynArray *array;
  init(array);
  printf("capacity: %d, count: %d\n", array->capacity, array->count);
  printf("buffer address: %p\n", &array->buffer);
  append(array, "test test test", 14);
  printf("new capacity: ");
  // append to it within its capacity
  // append to it beyond its capacity
  // free the vector
  return EXIT_SUCCESS;
}*/

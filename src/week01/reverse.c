#include <stdio.h>
#include <string.h>

#include "reverse.h"

void swap(char *left, char *right) {
  char temp;

  temp = *left;
  *left = *right;
  *right = temp;
}

void reverse(char *str) {
  if (str == NULL)
    return;
  int length = strlen(str);
  if (length < 2)
    return;

  char *start = str;
  char *end = str + length - 1;

  while (start < end) {
    swap(start, end);
    ++start;
    --end;
  }
}

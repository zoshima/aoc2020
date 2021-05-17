#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_NaN(const char *val) {
  int i = strlen(val);

  while (i--) {
    if (val[i] >= '0' && val[i] <= '9')
      continue;

    return true;
  }

  return false;
}

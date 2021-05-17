#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LINES 200
#define TARGET_SUM 2020

void load_input();
bool includes(int, int);

int input[INPUT_LINES];
int cache[INPUT_LINES];

int main() {
  load_input();

  for (int i = 0; i < INPUT_LINES - 2; i++) {
    int target_sum_i = TARGET_SUM - input[i];
    int cache_index = -1;

    for (int j = i + 1; j < INPUT_LINES; j++) {
      int target_sum_j = target_sum_i - input[j];

      if (includes(cache_index + 1, target_sum_j)) {
        printf("%d\n", input[i] * input[j] * target_sum_j);
        return 0;
      } else {
        cache[++cache_index] = input[j];
      }
    }
  }

  return 0;
}

bool includes(int lim, int value) {
  for (int i = 0; i < lim; i++) {
    if (cache[i] == value) {
      return true;
    }
  }

  return false;
}

void load_input() {
  FILE *file = fopen("../input/day1.txt", "r");

  for (int i = 0; i < INPUT_LINES; i++) {
    fscanf(file, "%d", &input[i]);
  }
}

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <quicksort.h>

#define NUM_LINES 743
#define NUM_COLS 11

void load_input();
int parse_sequence();

char input[NUM_LINES][NUM_COLS];

int main() {
  load_input();

  int row, col, id;
  int ids[NUM_LINES];

  for (int i = 0; i < NUM_LINES; i++) {
    row = parse_sequence(input[i], 0, 7, 0, 127);
    col = parse_sequence(input[i], 7, 10, 0, 7);

    id = 8 * row + col;

    ids[i] = id;
  }

  quicksort(ids, 0, NUM_LINES);

  for (int i = 0; i < NUM_LINES - 1; i++) {
    if (ids[i + 1] - ids[i] != 1) {
      printf("%d\n", ids[i] + 1);
      return 0;
    }
  }

  return 0;
}

int parse_sequence(const char *seq, int from, int to, int lb, int ub) {
  for (int i = from; i < to; i++) {
    int incr = (int)ceil((ub - lb) / 2.0);

    switch (seq[i]) {
    case 'B':
    case 'R':
      lb += incr;
      break;
    case 'F':
    case 'L':
      ub -= incr;
      break;
    default:
      return -1;
    }
  }

  return lb;
}

void load_input() {
  FILE *file = fopen("../input/day5.txt", "r");

  for (int i = 0; i < NUM_LINES; i++) {
    fscanf(file, "%s", input[i]);
  }

  fclose(file);
}

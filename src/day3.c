#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LINES 323
#define INPUT_COLS 31

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  int right;
  int down;
} Strategy;

void load_input();

bool input[INPUT_LINES][INPUT_COLS] = {false};

bool has_tree(const Position *position) {
  int rep_count = position->x / INPUT_COLS;
  int x = position->x - rep_count * INPUT_COLS;

  return input[position->y][x];
}

bool traverse(Position *current_position, const Strategy *strategy) {
  current_position->y = current_position->y + strategy->down;
  current_position->x = current_position->x + strategy->right;

  if (current_position->y >= INPUT_LINES) {
    return false;
  }

  return true;
}

int main() {
  load_input();

  Strategy strategies[] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}, {0}};
  Position current_position;

  int result = 1;
  int count = 0;

  for (int i = 0; strategies[i].right; i++) {
    count = 0;
    current_position.x = 0;
    current_position.y = 0;

    while (traverse(&current_position, &strategies[i])) {
      if (has_tree(&current_position)) {
        count++;
      }
    }

    printf("strat: { right: %d, down: %d }, count: %d\n", strategies[i].right,
           strategies[i].down, count);

    result *= count;
  }

  printf("%d\n", result);

  return 0;
}

void load_input() {
  FILE *file = fopen("../input/day3.txt", "r");

  char c;

  for (int i = 0; i < INPUT_LINES; i++) {
    for (int j = 0; j < INPUT_COLS; j++) {
      c = (char)fgetc(file);

      if (c == '#') {
        input[i][j] = true;
      }
    }

    c = fgetc(file);

    if (c != EOF && c != '\n') {
      printf("expected '\\n', but found '%c' on line %d\n", c, i);
      exit(1);
    };
  }

  fclose(file);
}

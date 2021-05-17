#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 2001
#define BUFFER_SIZE 255
#define LINE_INCREMENT 5
#define GROUP_INCREMENT 5
#define ASCII_RANGE 256

char ***groups;
int *group_lengths;

int load_input();

int main() {
  int num_groups = load_input();
  int answers[ASCII_RANGE] = {};
  int sum = 0;

  for (int i = 0; i < num_groups; i++) { // group
    int num_lines = group_lengths[i];
    int loc_answers[ASCII_RANGE] = {};

    for (int j = 0; j < num_lines; j++) { // person
      int slen = strlen(groups[i][j]);

      for (int k = 0; k < slen; k++) { // answer
        loc_answers[groups[i][j][k]] += 1;
      }
    }

    for (int j = 0; j < ASCII_RANGE; j++) {
      if (loc_answers[j] == num_lines) {

        answers[j] += 1;
      }
    }
  }

  for (int i = 0; i < ASCII_RANGE; i++) {
    sum += answers[i];
  }

  printf("%d\n", sum);

  return 0;
}

int load_input() {
  FILE *file = fopen("../input/day6.txt", "r");

  char buf[BUFFER_SIZE];
  char **group;

  int num_lines = 0, num_groups = 0;
  int slen;

  groups = (char ***)malloc(sizeof(char **) * GROUP_INCREMENT);
  group_lengths = (int *)malloc(sizeof(int) * GROUP_INCREMENT);

  group = (char **)malloc(sizeof(char *) * LINE_INCREMENT);

  while (fgets(buf, BUFFER_SIZE, file) != NULL) {
    slen = strlen(buf);

    // group end
    if (slen <= 1) {
      group = (char **)realloc(group, sizeof(char **) * num_lines);

      groups[num_groups] = group;
      group_lengths[num_groups] = num_lines;

      num_groups++;

      if (num_groups % GROUP_INCREMENT == 0) {
        groups = (char ***)realloc(groups, (num_groups + GROUP_INCREMENT) *
                                               sizeof(char ***));
        group_lengths = (int *)realloc(
            group_lengths, (num_groups + GROUP_INCREMENT) * sizeof(int *));
      }

      num_lines = 0;

      group = (char **)malloc(sizeof(char *) * LINE_INCREMENT);

      continue;
    }

    buf[--slen] = '\0';

    group[num_lines] = (char *)malloc(sizeof(char) * (slen + 1));

    strcpy(group[num_lines], buf);

    num_lines++;

    if (num_lines % LINE_INCREMENT == 0) {
      group = (char **)realloc(group,
                               (num_lines + LINE_INCREMENT) * sizeof(char *));
    }
  }

  group = (char **)realloc(group, sizeof(char **) * num_lines);

  groups[num_groups] = group;
  group_lengths[num_groups] = num_lines;

  groups = (char ***)realloc(groups, num_groups * sizeof(char **));
  group_lengths = (int *)realloc(group_lengths, num_groups * sizeof(int *));

  fclose(file);

  return num_groups + 1;
}

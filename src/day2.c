#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LINES 1000
#define MAX_LINE_LENGTH 30

typedef struct {
  char letter;
  int min;
  int max;
} Policy;

typedef struct {
  Policy policy;
  char *password;
} Password;

void load_input();
int is_valid(const Password*);

Password passwords[INPUT_LINES];

int main() {
  load_input();

  int c = 0;

  for (int i = 0; i < INPUT_LINES; i++) {
    c += is_valid(&passwords[i]);
  }

  printf("%d\n", c);

  return 0;
}

inline int is_valid(const Password* pw) {
  int match_a = pw->password[pw->policy.min - 1] == pw->policy.letter;
  int match_b = pw->password[pw->policy.max - 1] == pw->policy.letter;

  return match_a ^ match_b; // xor. true for 1|0 and 0|1, but false for 1|1 and 0|0
}

void load_input() {
  FILE *file = fopen("../input/day2.txt", "r");

  for (int i = 0; i < INPUT_LINES; i++) {
    Password *password = &passwords[i];
    Policy *policy = &password->policy;

    password->password = (char *)malloc(sizeof(char) * MAX_LINE_LENGTH);

    int res = fscanf(file, "%d-%d %c: %s", &policy->min, &policy->max,
                     &policy->letter, password->password);

    password->password = (char *)realloc(
        password->password, sizeof(char) * strlen(password->password));

    if (res != 4) {
      printf("failed to read line: %d\n", i);
      exit(1);
    }
  }

  fclose(file);
}

#include <err.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <char_extensions.h>

#define PNAME_LEN 4 // 3+1
#define PVAL_LEN 21
#define PW_INCREMENT 2

typedef struct {
  char *byr;
  char *iyr;
  char *eyr;
  char *hgt;
  char *hcl;
  char *ecl;
  char *pid;
  char *cid;
} Passport;

bool is_valid_range_prop(const char *, int, int);
bool is_valid_regex_prop(const char *, const regex_t *);
bool is_valid(const Passport *);
void set_property(Passport *, char[PNAME_LEN], char[PVAL_LEN]);
int read_input();

Passport *passports;
regex_t hex_match, col_match, pid_match;

int main() {
  if (regcomp(&hex_match, "^#[0-9a-f]{6}$", REG_EXTENDED)) {
    err(1, "failed to compile hex_match regex\n");
  }

  if (regcomp(&col_match, "^amb|blu|brn|gry|grn|hzl|oth$", REG_EXTENDED)) {
    err(1, "failed to compile col_match regex\n");
  }

  if (regcomp(&pid_match, "^[0-9]{9}$", REG_EXTENDED)) {
    err(1, "failed to compile pid_match regex\n");
  }

  int inputlen = read_input();
  int count = 0;

  for (int i = 0; i < inputlen; i++) {
    count += is_valid(&passports[i]);
  }

  printf("%d\n", count);

  regfree(&hex_match);
  regfree(&col_match);
  regfree(&pid_match);

  return 0;
}

bool is_valid_range_prop(const char *prop, int min, int max) {
  int val;

  if (prop == NULL || is_NaN(prop) || (val = atoi(prop)) < min || val > max) {
    return false;
  }

  return true;
}

bool is_valid_regex_prop(const char *prop, const regex_t *regex) {
  if (prop == NULL || regexec(regex, prop, 0, NULL, 0)) {
    return false;
  }

  return true;
}

bool is_valid(const Passport *passport) {
  if (!is_valid_range_prop(passport->byr, 1920, 2002)) {
    return false;
  }

  if (!is_valid_range_prop(passport->iyr, 2010, 2020)) {
    return false;
  }

  if (!is_valid_range_prop(passport->eyr, 2020, 2030)) {
    return false;
  }

  if (!is_valid_regex_prop(passport->hcl, &hex_match)) {
    return false;
  }

  if (!is_valid_regex_prop(passport->ecl, &col_match)) {
    return false;
  }

  if (!is_valid_regex_prop(passport->pid, &pid_match)) {
    return false;
  }

  if (passport->hgt != NULL) {
    char unit = passport->hgt[strlen(passport->hgt) - 2];
    int measure = atoi(passport->hgt);

    switch (unit) {
    case 'c':
      if (measure < 150 || measure > 193) {
        return false;
      }
      break;
    case 'i':
      if (measure < 59 || measure > 76) {
        return false;
      }
      break;
    default:
      return false;
    }
  } else {
    return false;
  }

  return true;
}

void realloc_passports(int c_len) {
  int n_size = sizeof(Passport) * (PW_INCREMENT + c_len);

  if (c_len == 0) {
    passports = (Passport *)malloc(n_size);
  } else {
    passports = (Passport *)realloc(passports, n_size);
  }

  if (!passports) {
    err(1, "allocation failed");
  }

  for (int i = c_len; i < c_len + PW_INCREMENT; i++) {
    passports[i].byr = NULL;
    passports[i].cid = NULL;
    passports[i].ecl = NULL;
    passports[i].eyr = NULL;
    passports[i].hcl = NULL;
    passports[i].hgt = NULL;
    passports[i].iyr = NULL;
    passports[i].pid = NULL;
  }
}

int read_input() {
  FILE *file = fopen("../input/day4.txt", "r");

  int c, pc;

  char pbuf[PNAME_LEN] = ""; // buffer for property name
  char vbuf[PVAL_LEN] = "";  // buffer for property value

  int i_pbuf = 0, i_vbuf = 0, i_arr = 0;

  bool vbufr = false; // true: reading into vbuf

  realloc_passports(0);

  Passport *current_passport = &passports[i_arr];

  while ((c = fgetc(file)) != EOF) {
    switch (c) {
    case ':':
      vbufr = true;
      break;
    case '\n':
      if (pc == '\n') {
        i_arr++;

        if (i_arr % PW_INCREMENT) {
          realloc_passports(i_arr);
        }

        current_passport = &passports[i_arr];
        break;
      }
    case ' ':
      pbuf[i_pbuf] = '\0';
      vbuf[i_vbuf] = '\0';

      set_property(current_passport, pbuf, vbuf);

      vbufr = false;
      i_pbuf = 0;
      i_vbuf = 0;

      break;
    default:
      if (vbufr) {
        if (i_vbuf >= PVAL_LEN - 1) {
          err(1, "invalid vlue length: '%s'", pbuf);
        }

        vbuf[i_vbuf++] = c;
      } else {
        if (i_pbuf >= PNAME_LEN - 1) {
          err(1, "invalid property length: '%s'", pbuf);
        }

        pbuf[i_pbuf++] = c;
      }

      break;
    }

    pc = c;
  }

  fclose(file);

  passports = (Passport *)realloc(passports, sizeof(Passport) * (i_arr + 1));

  if (!passports) {
    err(1, "shortening realloc failed");
  }

  return i_arr + 1;
}

// does not free, only for init
inline void set_property(Passport *passport, char pname[PNAME_LEN],
                         char pval[PVAL_LEN]) {
  char *val = (char *)malloc(sizeof(char) * (strlen(pval) + 1));

  strcpy(val, pval);

  switch (pname[0]) {
  case 'b':
    passport->byr = val;
    break;
  case 'i':
    passport->iyr = val;
    break;
  case 'p':
    passport->pid = val;
    break;
  case 'c':
    passport->cid = val;
    break;
  case 'e':
    if (pname[1] == 'y') {
      passport->eyr = val;
    } else {
      passport->ecl = val;
    }
    break;
  case 'h':
    if (pname[1] == 'g') {
      passport->hgt = val;
    } else {
      passport->hcl = val;
    }
    break;
  default:
    err(1, "invalid property name '%s'", pname);
  }
}

#include "../include/string_extensions.h"

namespace extensions {
vector<string> String::Split(const string &str, string regex_str) {
  vector<string> result;
  regex regex(regex_str);

  sregex_token_iterator iter(str.begin(), str.end(), regex,
                             -1); // -1: select non matched
  sregex_token_iterator end;

  while (iter != end) {
    result.push_back(*iter);
    iter++;
  }

  return result;
}

vector<string> String::Match(const string &str, string regex_str) {
  vector<string> result;
  regex regex(regex_str);

  sregex_token_iterator iter(str.begin(), str.end(), regex);
  sregex_token_iterator end;

  while (iter != end) {
    result.push_back(*iter);
    iter++;
  }

  return result;
}
} // namespace extensions

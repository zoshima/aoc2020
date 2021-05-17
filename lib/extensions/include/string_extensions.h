#pragma once

#include <regex>
#include <string>
#include <vector>

using namespace std;

namespace extensions {
class String {
public:
  static vector<string> Split(const string &str, string regex_str);
  static vector<string> Match(const string &str, string regex_str);
};
} // namespace extensions

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <string_extensions.h>

using namespace std;

using container_map = unordered_map<string, unordered_set<string>>;
using containing_map = unordered_map<string, unordered_map<string, int>>;

void FindContainers(container_map& map, unordered_set<string>& containers, string bag) {
  for (auto& parent : map[bag]) {
    containers.insert(parent);

    FindContainers(map, containers, parent);
  }
}

int CountContent(containing_map& map, string bag) {
  int count = 0;

  for (auto& it : map[bag]) {
    const int num_child_bags = map[bag][it.first];

    count += num_child_bags + num_child_bags * CountContent(map, it.first);
  }

  return count;
}

int main() {
  fstream file("../input/day7.txt", ios::in);
  string line;
  container_map container_map; // key is a bag, value is a list of bags that can contain it
  containing_map containing_map; // key is a bag, value is a list of bags it can contain

  while (getline(file, line)) {
    const vector<string> cols = extensions::String::Split(line, " bag[s]? "); // ex. [ "dull magenta", "contain 5 dim plum bags, 5 dark coral bags. ]
    const vector<string> svalues = extensions::String::Match(cols[1], "[0-9]+.*?(?= bag)"); // ex [ "5 dim plum", "5 dark coral" ]
    const string key = cols[0]; // ex "dull magenta"

    vector<pair<string, int>> values;

    containing_map.emplace(key, unordered_map<string, int>());

    for (const string &value : svalues) {
      stringstream ss(value); // ex "5 dim plum"
      pair<string, int> pair;

      ss >> pair.second; // ex 5
      getline(ss, pair.first); // ex " dim plum"
      pair.first.erase(0, 1);

      values.push_back(pair);

      if (container_map.find(pair.first) == container_map.end()) {
        container_map.emplace(pair.first, unordered_set<string>());
      }

      container_map[pair.first].insert(key);
      containing_map[key].emplace(pair.first, pair.second);
    }
  }

  file.close();

  unordered_set<string> set;
  FindContainers(container_map, set, "shiny gold");
  cout << set.size() << endl;

  int result = CountContent(containing_map, "shiny gold");
  cout << result << endl;

  return 0;
}

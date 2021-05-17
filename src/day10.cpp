#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> input;

void LoadInput() {
  ifstream file{"../input/day10.txt"};
  string line;

  while (getline(file, line)) {
    input.push_back(stoi(line));
  }

  file.close();
}

// returns input indexes
vector<int> GetAdapters(const int &from, const int &rating) {
  vector<int> adapters;

  const int min_rating = rating - 3;
  const int max_rating = rating + 3;

  for (int i = from; i < input.size(); i++) {
    if (input[i] < min_rating) {
      continue;
    }

    if (input[i] > max_rating) {
      break;
    }

    adapters.push_back(i);
  }

  return adapters;
}

int main() {
  LoadInput();

  constexpr int charging_outlet_rating = 0;

  const int max_adapter = *max_element(input.begin(), input.end());
  const int *current_adapter = &charging_outlet_rating;

  int current_adapter_index = -1;

  unordered_map<int, int> jolts_map; // jolts_diff:count
  vector<int> diffs;

  jolts_map[3] = 1; // built in adapter diff

  sort(input.begin(), input.end());

  while (*current_adapter != max_adapter) {
    const vector<int> adapter_indexes =
        GetAdapters(current_adapter_index + 1, *current_adapter);

    for (const int &i : adapter_indexes) {
      const int diff = abs(*current_adapter - input[i]);

      jolts_map[diff] += 1;
      diffs.push_back(diff);

      current_adapter_index = i;
      current_adapter = &input[current_adapter_index];
    }
  }

  cout << jolts_map[1] * jolts_map[3] << endl; // part 1

  diffs.push_back(3);

  /* permutations for optional number sequences
  52 49     48 47 46     45 42
  perms: 2^3 - 1 = 7

  23 20     19 18        17 14
  perms: 2^2 = 4

  28 25     24           23 20
  perms: 2^1 = 2
  */

  constexpr int kPerms_3 = 7; // 2^3 - 1
  constexpr int kPerms_2 = 4; // 2^2
  constexpr int kPerms_1 = 2; // 2^1

  int num_optionals = 0;
  long sum = 1;

  for (int i = 0; i < diffs.size() - 1; i++) {
    // optionals are always 1s not followed by 3s
    if (diffs[i] == 1 && diffs[i + 1] != 3) {
      num_optionals++;
    } else if (num_optionals) {
      switch (num_optionals) {
      case 1:
        sum *= kPerms_1;
        break;
      case 2:
        sum *= kPerms_2;
        break;
      case 3:
        sum *= kPerms_3;
        break;
      default:
        cout << "unexpected sequence of optionals: " << num_optionals << endl;
        exit(1);
      }

      num_optionals = 0;
    }
  }

  cout << sum << endl; // part 2

  return 0;
}

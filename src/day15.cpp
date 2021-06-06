#include <iostream>
#include <unordered_map>

using namespace std;

const int kTarget = 30000000 - 1;
const int kInputSize = 6;

int main() {
  unordered_map<int, int> spoken_numbers(
      {{1, 0}, {12, 1}, {0, 2}, {20, 3}, {8, 4}, {16, 5}});

  auto end = spoken_numbers.end();

  int num_spoken = 0; // first spoken after last starting number is always 0

  for (int i = kInputSize; i < kTarget; ++i) {
    auto it = spoken_numbers.find(num_spoken);

    if (it != end) {
      num_spoken = i - it->second;

      it->second = i;
    } else {
      spoken_numbers.insert({num_spoken, i});

      num_spoken = 0;
    }
  }

  cout << num_spoken << endl;
}

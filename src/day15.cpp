#include <iostream>
#include <vector>

using namespace std;

const int input[] = {1, 12, 0, 20, 8, 16};

int FindLastIndex(vector<int> &v, int val) {
  for (int i = v.size() - 1; i >= 0; --i) {
    if (v[i] == val) {
      return i;
    }
  }

  return -1;
}

int main() {
  vector<int> spoken_numbers(begin(input), end(input));
  int num_spoken = 0; // first spoken after last starting number is always 0

  for (int i = spoken_numbers.size(); i < 2020 - 1; i++) {
    int index = FindLastIndex(spoken_numbers, num_spoken);

    spoken_numbers.push_back(num_spoken);

    if (index == -1) {
      num_spoken = 0;
    } else {
      num_spoken = i - index;
    }
  }

  cout << num_spoken << endl;
}

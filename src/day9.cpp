#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct ContiguousSet {
  int from, to;
  long min, max;

  bool operator==(const ContiguousSet &other) const {
    return from == other.from && to == other.to && min == other.min &&
           max == other.max;
  }
  bool operator!=(const ContiguousSet &other) const { return !(*this == other); }
};

struct Addendants {
  long a, b;

  bool operator==(const Addendants &other) const {
    return a == other.a && b == other.b;
  }
  bool operator!=(const Addendants &other) const { return !(*this == other); }
};

constexpr int preample = 25;
constexpr ContiguousSet kNullContiguousSet{-1, -1, -1, -1};
constexpr Addendants kNullAddendants{-1, -1};

vector<long> input;

void LoadInput() {
  ifstream file{"../input/day9.txt"};
  string line;

  while (getline(file, line)) {
    input.push_back(stol(line));
  }
}

Addendants GetAddendants(long num, int index) {
  for (int i = index - preample; i < index - 1; i++) {
    if (input[i] >= num) {
      continue;
    }

    for (int j = i + 1; j < index; j++) {
      if (input[j] >= num) {
        continue;
      }

      if (input[i] + input[j] == num) {
        return Addendants{input[i], input[j]};
      }
    }
  }

  return kNullAddendants;
}

ContiguousSet GetContiguousSet(long num) {
  const int lim = input.size() / 2;
  int setLength = 2;

  do {
    for (int i = 0; i < input.size() - setLength; i++) {
      long sum = 0;
      long min = input[i];
      long max = min;

      for (int j = 0; j < setLength; j++) {
        const long _num = input[i + j];

        sum += _num;

        if (_num < min) {
          min = _num;
        }

        if (_num > max) {
          max = _num;
        }
      }

      if (sum == num) {
        return ContiguousSet{i, i + setLength, min, max};
      }
    }
  } while (++setLength < lim);

  return kNullContiguousSet;
}

int main() {
  LoadInput();

  for (int i = preample; i < input.size(); i++) {
    const long num = input[i];
    const Addendants addendants = GetAddendants(num, i);

    if (addendants == kNullAddendants) {
      cout << num << endl;

      const ContiguousSet set = GetContiguousSet(num);

      if (set != kNullContiguousSet) {
        cout << set.min + set.max << endl;
        break;
      }
    }
  }

  return 0;
}

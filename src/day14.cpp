#include <bitset>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const regex maskPattern("^mask = ([X10]+)$");
const regex memPattern("^mem\\[(\\d+)\\] = (\\d+)$");

const int kMaskSize = 36;

void ApplyMask(unordered_map<unsigned long, int> &addresses, const int &value,
               const string &mask, bitset<kMaskSize> bset, int i = 0) {
  for (; i < kMaskSize; i++) {
    switch (mask[i]) {
    case '0':
      break;
    case '1':
      bset.set(i, 1);
      break;
    case 'X':
      bset.set(i, 1);
      ApplyMask(addresses, value, mask, bset, i + 1);
      bset.set(i, 0);
      ApplyMask(addresses, value, mask, bset, i + 1);
      return;
    }
  }

  addresses[bset.to_ulong()] = value;
}

int main() {
  ifstream file("../input/day14.txt");
  string line, mask;
  smatch sm;
  unordered_map<unsigned long, int> memory;

  while (getline(file, line)) {
    if (line[1] == 'a') {
      regex_search(line, sm, maskPattern);

      mask = sm[1];

      reverse(mask.begin(), mask.end());
    } else {
      regex_search(line, sm, memPattern);

      int index = stoi(sm[1]);
      int value = stoi(sm[2]);

      ApplyMask(memory, value, mask, bitset<kMaskSize>(index));
    }
  }

  unsigned long sum = 0;

  for (auto &pair : memory) {
    sum += pair.second;
  }

  cout << sum << endl;
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <bitset>

using namespace std;

const regex maskPattern("^mask = ([X10]+)$");
const regex memPattern("^mem\\[(\\d+)\\] = (\\d+)$");

const int kMaskSize = 36;

int main() {
  ifstream file("../input/day14.txt");
  string line, mask;
  smatch sm;
  unordered_map<int, unsigned long> memory;

  while (getline(file, line)) {
    if (line[1] == 'a') {
      regex_search(line, sm, maskPattern);

      mask = sm[1];
    } else {
      regex_search(line, sm, memPattern);

      int index = stoi(sm[1]);
      bitset<kMaskSize> value(stoi(sm[2]));

      for (int i = 0; i < kMaskSize; i++) {
        if (mask[i] == '1') {
          value.set(kMaskSize - i - 1, 1);
        } else if (mask[i] == '0') {
          value.set(kMaskSize - i - 1, 0);
        }
      }

      memory[index] = value.to_ulong();
    }
  }

  unsigned long sum = 0;

  for (auto &pair : memory) {
    sum += pair.second;
  }

  cout << sum << endl;
}

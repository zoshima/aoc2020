#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ship.h"

using namespace std;

vector<pair<char, int>> input;

void LoadInput() {
  ifstream file("../input/day12.txt");
  string line;

  while (getline(file, line)) {
    int value = stoi(line.substr(1));

    input.push_back(make_pair(line[0], value));
  }
}

int main() {
  LoadInput();

  Ship ship(kEast);

  for (auto &i : input) {
    ship.ProcessInstruction(i.first, i.second);
  }

  ship.Print();

  return 0;
}

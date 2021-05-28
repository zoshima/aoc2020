#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <sstream>

using namespace std;

const int kNumElements = 8; 
array<int, kNumElements> busIds;
int minTimestamp;

void LoadInput() {
  ifstream file("../input/day13.txt");
  string line;
  int i = 0;

  getline(file, line);

  minTimestamp = stoi(line);

  getline(file, line);

  file.close();

  stringstream ss(line);

  while (getline(ss, line, ',')) {
    if (line != "x") {
      busIds[i++] = stoi(line);
    } else {
      busIds[i++] = -1;
    }
  }
}

int main() {
  LoadInput();

  for (auto iter = busIds.begin(); iter != busIds.end(); iter++) {
    cout << *iter << endl;
  }

  return 1;
}

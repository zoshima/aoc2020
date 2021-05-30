#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> busIds;

void LoadInput() {
  ifstream file("../input/day13.txt");
  string line;

  getline(file, line);

  file.close();

  stringstream ss(line);

  while (getline(ss, line, ',')) {
    if (line != "x") {
      busIds.push_back(stoi(line));
    } else {
      busIds.push_back(1);
    }
  }
}

int main() {
  LoadInput();

  long ts = busIds[0];
  long inc = ts;

  for (int i = 1; i < busIds.size(); i++) {
    while ((ts + i) % busIds[i] != 0) {
      ts += inc;
    }

    inc = lcm(busIds[i], inc);
  }

  cout << ts << endl;

  return 1;
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using SeatMap = vector<vector<char>>;

constexpr int kNumRows = 97;
constexpr int kNumCols = 90;

constexpr char kFloor = '.';
constexpr char kEmptySeat = 'L';
constexpr char kOccupiedSeat = '#';

SeatMap input(kNumRows);

void LoadInput() {
  ifstream file{"../input/day11.txt"};
  string line;

  for (int i = 0; getline(file, line); i++) {
    input[i] = vector<char>(line.begin(), line.end());
  }

  file.close();
}

inline bool IsOccupied(const SeatMap &spots, int x, int y) {
  if (x < 0 || x >= kNumCols) {
    return false; // out of bounds
  }

  if (y < 0 || y >= kNumRows) {
    return false; // out of bounds
  }

  return spots[y][x] == kOccupiedSeat;
}

inline int NumOccupiedAdjuscent(const SeatMap &spots, int x, int y) {
  int numOccupied = 0;

  numOccupied += IsOccupied(spots, x - 1, y);     // west
  numOccupied += IsOccupied(spots, x + 1, y);     // east
  numOccupied += IsOccupied(spots, x, y - 1);     // north
  numOccupied += IsOccupied(spots, x, y + 1);     // south
  numOccupied += IsOccupied(spots, x - 1, y - 1); // northwest
  numOccupied += IsOccupied(spots, x + 1, y - 1); // northeast
  numOccupied += IsOccupied(spots, x - 1, y + 1); // southwest
  numOccupied += IsOccupied(spots, x + 1, y + 1); // southeast

  return numOccupied;
}

void UpdateState(const SeatMap &spots, int x, int y) {
  switch (spots[y][x]) {
  case kFloor:
    break;
  case kEmptySeat:
    if (!NumOccupiedAdjuscent(spots, x, y)) {
      input[y][x] = kOccupiedSeat;
    }
    break;
  case kOccupiedSeat:
    if (NumOccupiedAdjuscent(spots, x, y) >= 4) {
      input[y][x] = kEmptySeat;
    }
    break;
  }
}

bool Run() {
  const SeatMap spots = input; // readonly copy
  bool hasChanged = false;

  for (int y = 0; y < kNumRows; y++) {
    for (int x = 0; x < kNumCols; x++) {
      UpdateState(spots, x, y); // uses the copy to update input

      if (spots[y][x] != input[y][x]) {
        hasChanged = true;
      }
    }
  }

  return hasChanged;
}

inline void Print() {
  for (auto& row : input) {
    for (auto& spot : row) {
      cout << spot << " ";
    }

    cout << endl;
  }

  cout << endl;
}

int main() {
  LoadInput();

  while (Run()) {}

  int count = 0;

  for (auto& line : input) {
    for (auto& spot : line) {
      count += spot == kOccupiedSeat;
    }
  }

  cout << count << endl;

  return 0;
}

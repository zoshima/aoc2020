#include "room.h"
#include <fstream>
#include <iostream>

Room::Room(const Room &obj) {
  map = obj.map;
}

void Room::Load(ifstream &file) {
  string line;

  while (getline(file, line)) {
    map.push_back(vector<char>(line.begin(), line.end()));
  }

  file.close();
}

const char Room::Get(const int x, const int y) const {
  return map[y][x];
}

void Room::Set(const int x, const int y, const char& symbol) {
  map[y][x] = symbol;
}

bool Room::IsOccupied(const int x, const int y) const {
  if (!this->IsWithinBounds(x, y)) {
    return false;
  }

  return map[y][x] == kOccupiedSeat;
}

bool Room::IsWithinBounds(const int x, const int y) const {
  if (y < 0 || y >= map.size()) {
    return false;
  }

  if (x < 0 || x >= map[y].size()) {
    return false;
  }

  return true;
}

void Room::Print() const {
  for (auto &line : map) {
    for (auto &ch : line) {
      std::cout << ch << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

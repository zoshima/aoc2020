#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;

using charmap = vector<vector<char>>;

static constexpr char kFloor = '.';
static constexpr char kEmptySeat = 'L';
static constexpr char kOccupiedSeat = '#';

class RoomIterator {
public:
  RoomIterator(charmap *_map, const int _x, const int _y)
      : map(_map), x(_x), y(_y) {}

  const pair<int, int> Position() const { return make_pair(x, y); }

  const char &operator*() { return (*map)[y][x]; }

  RoomIterator &operator++() {
    if (x >= map->at(y).size() - 1) {
      ++y;
      x = 0;
    } else {
      ++x;
    }

    return *this;
  }

  RoomIterator operator++(int) {
    RoomIterator it = *this;
    ++(*this);
    return it;
  }

  bool operator==(const RoomIterator &other) const {
    return this->x == other.x && this->y == other.y;
  }

  bool operator!=(const RoomIterator &other) const { return !(*this == other); }

private:
  const charmap *map;
  int x, y;
};

class Room {
public:
  Room() {}
  Room(const Room &obj);

  void Load(ifstream &file);

  const char Get(const int x, const int y) const;
  void Set(const int x, const int y, const char& symbol);

  bool IsOccupied(const int x, const int y) const;
  bool IsWithinBounds(const int x, const int y) const;

  void Print() const;

  RoomIterator begin() { return RoomIterator(&map, 0, 0); }
  RoomIterator end() {
    return RoomIterator(&map, 0, map.size());
  }

private:
  charmap map;
};

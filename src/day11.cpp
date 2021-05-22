#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "room.h"

using namespace std;

bool CanTraverse(const Room &room, int x, int y, const int incX,
                 const int incY) {
  x += incX;
  y += incY;

  while (room.IsWithinBounds(x, y)) {
    const char symbol = room.Get(x, y);

    switch (symbol) {
    case kEmptySeat:
      return true;
      break;
    case kOccupiedSeat:
      return false;
      break;
    }

    x += incX;
    y += incY;
  }

  return true;
}

int CountOccupiedWithinSight(const Room &room, int x, int y) {
  int count = 0;

  count += !CanTraverse(room, x, y, 0, -1);  // north
  count += !CanTraverse(room, x, y, 1, -1);  // northeast
  count += !CanTraverse(room, x, y, 1, 0);   // east
  count += !CanTraverse(room, x, y, 1, 1);   // southeast
  count += !CanTraverse(room, x, y, 0, 1);   // south
  count += !CanTraverse(room, x, y, -1, 1);  // southwest
  count += !CanTraverse(room, x, y, -1, 0);  // west
  count += !CanTraverse(room, x, y, -1, -1); // northwest

  return count;
}

bool TryUpdate(const Room &pristineRoom, Room &room, int x, int y) {
  const char symbol = room.Get(x, y);

  if (room.Get(x, y) == kFloor) {
    return false;
  }

  int count = CountOccupiedWithinSight(pristineRoom, x, y);

  switch (symbol) {
  case kEmptySeat:
    if (count == 0) {
      room.Set(x, y, kOccupiedSeat);
      return true;
    }
    break;
  case kOccupiedSeat:
    if (count > 4) {
      room.Set(x, y, kEmptySeat);
      return true;
    }
    break;
  }

  return false;
}

int main() {
  ifstream file("../input/day11.txt");
  Room room;
  bool isUpdated = false;
  int numOccupied = 0;
  int x, y;

  room.Load(file);

  do {
    Room pristineRoom{room};
    isUpdated = false;

    for (auto iter = room.begin(); iter != room.end(); ++iter) {
      tie(x, y) = iter.Position();

      if (TryUpdate(pristineRoom, room, x, y)) {
        isUpdated = true;
      }
    }

    /* room.Print(); */
  } while (isUpdated);

  for (auto iter = room.begin(); iter != room.end(); ++iter) {
    numOccupied += *iter == kOccupiedSeat;
  }

  cout << numOccupied << endl;

  return 0;
}

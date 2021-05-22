#pragma once

#include <iostream>
#include <unordered_map>

constexpr char kNorth = 'N';
constexpr char kWest = 'W';
constexpr char kSouth = 'S';
constexpr char kEast = 'E';
constexpr char kLeft = 'L';
constexpr char kRight = 'R';
constexpr char kForward = 'F';

class Ship {
public:
  Ship(char _heading) {
    heading = _heading;
    xoff = 0;
    yoff = 0;

    switch (heading) {
    case kEast:
      bearing = 90;
      break;
    case kSouth:
      bearing = 180;
      break;
    case kWest:
      bearing = 260;
      break;
    default:
      bearing = 0;
    }
  }

  void ProcessInstruction(const char direction, const int magnitude) {
    switch (direction) {
    case kLeft:
      Rotate(-1 * magnitude);
      break;
    case kRight:
      Rotate(magnitude);
      break;
    case kForward:
      Move(heading, magnitude);
      break;
    default:
      Move(direction, magnitude);
    }
  }

  void Print() {
    int north = yoff < 0 ? abs(yoff) : 0;
    int south = yoff >= 0 ? yoff : 0;
    int west = xoff < 0 ? abs(xoff) : 0;
    int east = xoff >= 0 ? xoff : 0;

    int manhd = north + south + west + east;

    std::cout << north << "N " << west << "W " << south << "S " << east
              << "E, heading " << heading << ", bearing " << bearing << ", " << manhd << "manhd"
              << std::endl;
  }

private:
  char heading; // compass direction
  int bearing;  // degree offset
  int xoff;
  int yoff;

  void Move(const char dir, int magnitude) {
    switch (dir) {
    case kNorth:
      yoff -= magnitude;
      break;
    case kSouth:
      yoff += magnitude;
      break;
    case kWest:
      xoff -= magnitude;
      break;
    case kEast:
      xoff += magnitude;
      break;
    }
  }

  void Rotate(int degrees) {
    bearing += degrees;

    if (bearing < 0) {
      bearing = bearing + 360;
    } else if (bearing >= 360) {
      bearing = bearing - 360;
    }

    if (bearing < 90) {
      heading = kNorth;
    } else if (bearing < 180) {
      heading = kEast;
    } else if (bearing < 270) {
      heading = kSouth;
    } else {
      heading = kWest;
    }
  }
};

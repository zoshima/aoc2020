#pragma once

#include <iostream>
#include <sstream>
#include <string>
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
  Ship() {
    shipPos = std::make_pair(0, 0);
    waypointPos = std::make_pair(10, 1);
  }

  void ProcessInstruction(const char action, const uint value) {
    switch (action) {
    case kNorth:
      MoveWaypoint(false, value);
      break;
    case kSouth:
      MoveWaypoint(false, -1 * value);
      break;
    case kEast:
      MoveWaypoint(true, value);
      break;
    case kWest:
      MoveWaypoint(true, -1 * value);
      break;
    case kLeft:
      RotateWaypointCCW(value); 
      break;
    case kRight:
      RotateWaypointCW(value);
      break;
    case kForward:
      MoveShip(value);
      break;
    }
  }

  void Print() {
    std::cout << "SHIP: " << ToString(shipPos) << std::endl;
    std::cout << "WAYPOINT: " << ToString(waypointPos) << std::endl;
  }

private:
  std::pair<int, int> shipPos;     // x, y
  std::pair<int, int> waypointPos; // x, y

  void MoveShip(const int value) {
    shipPos.first += value * waypointPos.first;
    shipPos.second += value * waypointPos.second;
  }

  void MoveWaypoint(const bool isHorizontal, const int value) {
    if (isHorizontal) {
      waypointPos.first += value;
    } else {
      waypointPos.second += value;
    }
  }

  void RotateWaypointCW(const int value) {
    switch (value) {
    case 90:
      std::swap(waypointPos.first, waypointPos.second);
      waypointPos.second *= -1;
      break;
    case 180:
      waypointPos.first *= -1;
      waypointPos.second *= -1;
      break;
    case 270:
      std::swap(waypointPos.first, waypointPos.second);
      waypointPos.first *= -1;
      break;
    default:
      throw std::runtime_error("invalid rotation value: " +
                               std::to_string(value));
    }
  }

  void RotateWaypointCCW(const int value) {
    switch (value) {
    case 90:
      std::swap(waypointPos.first, waypointPos.second);
      waypointPos.first *= -1;
      break;
    case 180:
      waypointPos.first *= -1;
      waypointPos.second *= -1;
      break;
    case 270:
      std::swap(waypointPos.first, waypointPos.second);
      waypointPos.second *= -1;
      break;
    default:
      throw std::runtime_error("invalid rotation value: " +
                               std::to_string(value));
    }
  }

  const std::string ToString(std::pair<int, int> &pos) const {
    int south = pos.second < 0 ? abs(pos.second) : 0;
    int north = pos.second >= 0 ? pos.second : 0;
    int west = pos.first < 0 ? abs(pos.first) : 0;
    int east = pos.first >= 0 ? pos.first : 0;

    int manhd = north + south + west + east;

    std::stringstream ss;

    ss << north << "N " << west << "W " << south << "S " << east << "E, manhd "
       << manhd;

    return ss.str();
  }
};

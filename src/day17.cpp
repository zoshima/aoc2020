#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "cube.cpp"

using namespace std;

int main() {
  Cube::CubeContainer cube_container;

  {
    ifstream file("../input/day17.txt");
    int x{0}, y{0};
    char c;

    while (file >> noskipws >> c) {
      switch (c) {
        case '#':
          cube_container.AddActive({x, y, 0});
          ++x;
          break;
        case '.':
          ++x;
          break;
        default:
          x = 0;
          ++y;
      }
    }
  }

  for (size_t i = 0; i < 6; i++) {
    vector<Cube::Cube> grid = cube_container.GetGrid();
    const Cube::CubeContainer cube_container_snapshot{cube_container};

    for (const Cube::Cube &cube : grid) {
      vector<Cube::Cube> neighbours =
          cube_container_snapshot.GetActiveNeighbours(cube);
      const int neighbours_size = neighbours.size();
      const bool is_active = cube_container_snapshot.IsActive(cube);

      if (is_active) {
        if (neighbours.size() != 2 && neighbours.size() != 3) {
          cube_container.RemoveActive(cube);
        }
      } else {
        if (neighbours.size() == 3) {
          cube_container.AddActive(cube);
        }
      }
    }

    // cout << "Cycle: " << i + 1 << endl;
    // cube_container.Print();
  }

  cout << cube_container.ActiveSize() << endl;
}
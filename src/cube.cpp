#include <unordered_set>
#include <vector>

using namespace std;

namespace Cube {
struct Cube {
  int x, y, z, w;

  Cube() {}
  Cube(int x, int y, int z, int w) : x{x}, y{y}, z{z}, w{w} {}

  bool operator==(const Cube &other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z &&
           this->w == other.w;
  }

  struct HashFunction {
    size_t operator()(const Cube &cube) const {
      auto [x, y, z, w] = cube;

      string hash_string = to_string(x) + "x" + to_string(y) + "y" +
                           to_string(z) + "z" + to_string(w) + "w";

      return hash<string>{}(hash_string);
    };
  };
};

class Bounds {
 public:
  int min_x, min_y, min_z, min_w;
  int max_x, max_y, max_z, max_w;

  void Update(const Cube &cube) {
    UpdateValue(cube.x, min_x, max_x);
    UpdateValue(cube.y, min_y, max_y);
    UpdateValue(cube.z, min_z, max_z);
    UpdateValue(cube.w, min_w, max_w);
  }

 private:
  void UpdateValue(const int &bound, int &min, int &max) {
    if (bound <= min) {
      min = bound - 1;
    }

    if (bound >= max) {
      max = bound + 1;
    }
  }
};

class CubeContainer {
 public:
  CubeContainer() : bounds{0, 0, 0, 0, 0, 0, 0, 0} {}
  CubeContainer(const CubeContainer &other)
      : bounds{other.bounds}, active_cubes{other.active_cubes} {}

  void AddActive(Cube cube) {
    bounds.Update(cube);

    active_cubes.insert(cube);
  }

  void RemoveActive(const Cube &cube) { active_cubes.erase(cube); }

  bool IsActive(const Cube &cube) const {
    return active_cubes.find(cube) != active_cubes.end();
  }

  vector<Cube> GetActiveNeighbours(const Cube &cube) const {
    vector<Cube> neighbours;
    auto end = active_cubes.end();

    for (int z = cube.z - 1; z <= cube.z + 1; z++) {
      for (int x = cube.x - 1; x <= cube.x + 1; x++) {
        for (int y = cube.y - 1; y <= cube.y + 1; y++) {
          for (int w = cube.w - 1; w <= cube.w + 1; w++) {
            Cube neighbour{x, y, z, w};

            if (cube == neighbour) {
              continue;
            }

            auto it = active_cubes.find(neighbour);

            if (it != end) {
              neighbours.push_back(neighbour);
            }
          }
        }
      }
    }

    return neighbours;
  }

  vector<Cube> GetGrid() const {
    vector<Cube> grid;

    for (int x = bounds.min_x; x <= bounds.max_x; x++) {
      for (int y = bounds.min_y; y <= bounds.max_y; y++) {
        for (int z = bounds.min_z; z <= bounds.max_z; z++) {
          for (int w = bounds.min_w; w <= bounds.max_w; w++) {
            grid.push_back({x, y, z, w});
          }
        }
      }
    }

    return grid;
  }

  const size_t ActiveSize() const { return active_cubes.size(); }

 private:
  unordered_set<Cube, Cube::HashFunction> active_cubes;
  Bounds bounds;
};
}  // namespace Cube
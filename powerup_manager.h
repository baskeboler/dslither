#ifndef POWERUP_MANAGER_H
#define POWERUP_MANAGER_H
#include <map>
#include <vector>

#include "./color.h"
#include "./point_indexer.h"
#include "./powerup.h"

namespace slither {
using std::vector;

typedef uint64_t weight_t;
typedef color_rgba color_t;

typedef powerup<weight_t, color_t> powerup_t;

class powerup_manager {
  std::map<int, powerup_t> powerup_map;
  point_indexer index;
  uint64_t w, h;

  int boundedrand(int bound) const;

public:
  powerup_manager();
  vector<powerup_t> all();
  powerup_t byidx(int idx) const;
  int random_powerup();

  vector<powerup_t> find(const point_t &p);
};
} // namespace slither

#endif // POWERUP_MANAGER_H

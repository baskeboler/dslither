#include "./powerup_manager.h"
#include <utility>
#include <vector>

using std::vector;

int powerup_manager::boundedrand(int bound) const {
  return std::rand() % bound;
}

powerup_manager::powerup_manager() : w{500}, h{500} {}

vector<powerup_t> powerup_manager::all() {
  vector<powerup_t> res;
  for (auto &entry : index.all()) {
    res.push_back(powerup_map.at(entry.second));
  }
  return res;
}

powerup_t powerup_manager::byidx(int idx) const { return powerup_map.at(idx); }

int powerup_manager::random_powerup() {
  auto weight = rand() % 100;
  auto color = rand() & 0xffffff;
  powerup_t p;
  point_t pnt{boundedrand(w), boundedrand(h)};
  geo_point_index_value_t idxPosition = index.add(pnt);
  p.setColor(color);
  p.setWeight(weight);
  p.setPosition(idxPosition);
  powerup_map[idxPosition.second] = p;
  return idxPosition.second;
}

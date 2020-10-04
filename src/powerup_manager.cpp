#include "./powerup_manager.h"
#include <random>
#include <utility>
#include <vector>

namespace slither {
using std::vector;

int powerup_manager::boundedrand(int bound) const {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> dis(0, bound);
  return dis(gen);
}

powerup_manager::powerup_manager(const uint64_t &width, const uint64_t &height)
    : w{width}, h{height} {}

vector<powerup_t> powerup_manager::all() {
  vector<powerup_t> res;
  for (const auto &entry : index.all()) {
    res.push_back(powerup_map.at(entry.second));
  }
  return res;
}

powerup_t powerup_manager::byidx(int idx) const { return powerup_map.at(idx); }

int powerup_manager::random_powerup() {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<> weight_dis(10, 100);
  std::uniform_int_distribution<> x_dis(0, w);
  std::uniform_int_distribution<> y_dis(0, h);
  auto weight = weight_dis(gen);
  auto color = color_rgba::random();
  powerup_t p;
  point_t pnt{x_dis(gen), y_dis(gen)};
  geo_point_index_value_t idxPosition = index.add(pnt);
  p.setColor(color);
  p.setWeight(weight);
  p.setPosition(idxPosition);
  powerup_map[idxPosition.second] = p;
  return idxPosition.second;
}

vector<powerup_t> powerup_manager::find(const point_t &p) {
  int x = p.get<0>();
  int y = p.get<1>();
  box_t box{{x - 5, y - 5}, {x + 5, y + 5}};
  auto vals = index.intersects(box);
  vector<powerup_t> res;
  for (auto &v : vals) {
    res.push_back(powerup_map.at(v.second));
    index.remove(v);
    powerup_map.erase(v.second);
  }

  return res;
}
} // namespace slither
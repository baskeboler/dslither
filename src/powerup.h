#ifndef POWERUP_H
#define POWERUP_H
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

#include "./point_indexer.h"

namespace slither {

// using std::integral;

template <typename w, typename c> class powerup;

template <typename w, typename c>
std::ostream &operator<<(std::ostream &os, const powerup<w, c> &p);

template <typename WeightType, typename ColorType> class powerup {
  WeightType weight;
  ColorType color;
  geo_point_index_value_t position;

public:
  powerup() = default;
  powerup(const powerup<WeightType, ColorType> &other) = default;
  powerup(powerup<WeightType, ColorType> &&other) noexcept = default;
  powerup &operator=(powerup &&other) noexcept {
    weight = std::move(other.weight);
    color = std::move(other.color);
    position = std::move(other.position);
    return *this;
  }
  powerup &operator=(const powerup &other) {
    weight = other.weight;
    color = other.color;
    position = other.position;
    return *this;
  }

  WeightType getWeight() const { return weight; }
  void setWeight(const WeightType &value) { weight = value; }
  ColorType getColor() const { return color; }
  void setColor(const ColorType &value) { color = value; }
  geo_point_index_value_t getPosition() const { return position; }
  void setPosition(const geo_point_index_value_t &value) { position = value; }
  friend std::ostream &
  operator<<<WeightType, ColorType>(std::ostream &os,
                                    const powerup<WeightType, ColorType> &p);
};

template <typename w, typename c>
std::ostream &operator<<(std::ostream &os, const powerup<w, c> &p) {
  return os << "powerup{w=" << std::to_string(p.getWeight())
            << ", c=" << std::to_string(p.getColor())
            << ", pos=" << geo::wkt(p.getPosition()) << "}";
}
} // namespace slither

#endif // POWERUP_H

#include "color.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

color_rgba::color_rgba(const uint32_t &v) : value{v} {}

uint8_t color_rgba::r() const { return 0xff & value >> 24; }

uint8_t color_rgba::g() const { return 0xff & (value >> 16); }

uint8_t color_rgba::b() const { return 0xff & (value >> 8); }

uint8_t color_rgba::a() const { return 0xff & value; }

void color_rgba::setR(uint8_t r) {
  uint32_t val = 0 | (r << 24);
  value &= 0x00FFFFFF;
  value |= val;
}

void color_rgba::setG(uint8_t r) {
  uint32_t val = 0 | (r << 16);
  value &= 0xFF00FFFF;
  value |= val;
}

void color_rgba::setB(uint8_t r) {

  uint32_t val = 0 | (r << 8);
  value &= 0xFFFF00FF;
  value |= val;
}

void color_rgba::setA(uint8_t r) {
  uint32_t val = 0 | r;
  value &= 0xFFFFFF00;

  value |= val;
}

color_rgba &color_rgba::operator+(const color_rgba &other) {
  color_rgba res;

  res.setA(std::min(UINT8_MAX, a() + other.a()));
  res.setR(std::min(UINT8_MAX, r() + other.r()));
  res.setG(std::min(UINT8_MAX, g() + other.g()));
  res.setB(std::min(UINT8_MAX, b() + other.b()));
  return *new color_rgba{res};
}

color_rgba &color_rgba::operator+(const uint32_t &other) {
  return *this + color_rgba{other};
}

color_rgba &color_rgba::operator=(const color_rgba &other) {
  value = other.value;
  return *this;
}

bool color_rgba::operator==(const color_rgba &other) const {
  return value == other.value;
}

bool color_rgba::operator==(const uint32_t &v) const { return value == v; }

std::string color_rgba::css() const {
  std::stringstream ss;
  ss << "#" << std::setbase(16) << std::noshowbase << std::setfill('0')
     << std::setw(2) << static_cast<int>(r()) << std::setfill('0')
     << std::setw(2) << static_cast<int>(g()) << std::setfill('0')
     << std::setw(2) << static_cast<int>(b()) << std::setfill('0')
     << std::setw(2) << static_cast<int>(a());
  return ss.str();
}

std::ostream &operator<<(std::ostream &os, const color_rgba &c) {
  return os << std::setfill('0') << std::setbase(16) << std::showbase
            << "color{r=" << std::internal << std::setw(4)
            << static_cast<int>(c.r()) << ", g=" << std::internal
            << std::setw(4) << static_cast<int>(c.g())
            << ", b=" << std::internal << std::setw(4)
            << static_cast<int>(c.b()) << ", alpha=" << std::internal
            << std::setw(4) << static_cast<int>(c.a()) << "}";
}

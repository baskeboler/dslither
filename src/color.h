#ifndef COLOR_H
#define COLOR_H
#include <ostream>
#include <string>

class color_rgba {
  uint32_t value = 0;

public:
  color_rgba() = default;
  color_rgba(const color_rgba &other) : value{other.value} {};
  color_rgba(color_rgba &&other) noexcept : value{std::move(other.value)} {}
  explicit color_rgba(const uint32_t &v);
  ~color_rgba() = default;
  uint8_t r() const;
  uint8_t g() const;
  uint8_t b() const;
  uint8_t a() const;
  void setR(uint8_t r);
  void setG(uint8_t r);
  void setB(uint8_t r);
  void setA(uint8_t r);

  color_rgba &operator+(const color_rgba &other);
  color_rgba &operator+(const uint32_t &other);

  color_rgba &operator=(const color_rgba &other);
  color_rgba &operator=(color_rgba &&other) noexcept;
  bool operator==(const color_rgba &other) const;
  bool operator==(const uint32_t &v) const;

  std::string css() const;

  friend std::ostream &operator<<(std::ostream &, const color_rgba &);

  static color_rgba random();
};

std::ostream &operator<<(std::ostream &, const color_rgba &);

#endif // COLOR_H

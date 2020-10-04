#ifndef SLITH_H
#define SLITH_H
#include <list>
#include <ostream>

#include "./point_indexer.h"

namespace slither {

class slith_spec {
public:
  virtual ~slith_spec() = default;
  virtual std::list<point_t> points() const = 0;
};

class slith : public std::enable_shared_from_this<slith>, public slith_spec {
  enum Direction { Left, Right, Up, Down };
  std::list<geo_segment_index_value_t> segments;

  //  multipoint_t points;
  linestring_t _points;
  segment_indexer segment_idx;
  //  linestring_indexer linestring_idx;
  point_t head_position;
  int nextidx;
  Direction currentDirection = Right;
  typedef std::pair<int, int> int_pair;
  static constexpr int_pair LEFT = {-1, 0};
  static constexpr int_pair RIGHT = {1, 0};
  static constexpr int_pair UP = {0, 1};
  static constexpr int_pair DOWN = {0, -1};
  static constexpr int_pair direction(Direction d) {
    switch (d) {
    case Right:
      return RIGHT;
    case Left:
      return LEFT;
    case Up:
      return UP;
    case Down:
      return DOWN;
    default:
      return RIGHT;
    }
  }

public:
  slith();
  virtual ~slith() = default;
  point_t headpos() const;
  void chop_tail();
  void move(std::pair<int, int> d);
  void move(int dx, int dy);
  void moveleft();
  void moveright();
  void moveup();
  void movedown();
  void tick();
  int length() const;

  friend std::ostream &operator<<(std::ostream &, const slith &);

  // slith_spec interface
  virtual std::list<point_t> points() const override {
    std::list<point_t> res;
    res.push_back(head_position);
    for (const auto &s : segments) {
      res.push_back(s.first.second);
    }
    return res;
  }
};

std::ostream &operator<<(std::ostream &, const slith &);
} // namespace slither

#endif // SLITH_H

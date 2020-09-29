#ifndef SLITH_H
#define SLITH_H
#include <list>

#include "./point_indexer.h"

namespace slither {

class slith : public std::enable_shared_from_this<slith> {
  enum Direction { Left, Right, Up, Down };
  std::list<geo_segment_index_value_t> segments;

  //  multipoint_t points;
  linestring_t points;
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

  //  bool collides(slith &other) { segment_idx }
  //  void normalize() { segment_idx. }
};
} // namespace slither

#endif // SLITH_H

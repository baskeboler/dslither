#include "slith.h"
#include "./point_indexer.h"
#include <boost/geometry/io/io.hpp>

namespace slither {

slith::slith() : _points{{0, 0}}, head_position(0, 0) {}

point_t slith::headpos() const { return head_position; }

void slith::chop_tail() {
  auto v = segments.back();
  segment_idx.remove(v);
  segments.pop_back();

  _points.pop_back();
}

void slith::move(std::pair<int, int> d) { move(d.first, d.second); }

void slith::move(int dx, int dy) {
  point_t newhead{head_position.get<0>() + dx, head_position.get<1>() + dy};
  segment_t newsegment{newhead, head_position};
  geo_segment_index_value_t indexedsegment = segment_idx.add(newsegment);
  _points.insert(_points.begin(), newhead);
  segments.push_front(indexedsegment);
  head_position = newhead;
}

void slith::moveleft() { move(LEFT); }

void slith::moveright() { move(RIGHT); }

void slith::moveup() { move(UP); }

void slith::movedown() { move(DOWN); }

void slith::tick() { move(direction(currentDirection)); }

int slith::length() const { return _points.size(); }

std::ostream &operator<<(std::ostream &os, const slith &s) {
  return os << "slith{"
            << "head=" << boost::geometry::wkt(s.headpos())

            << "}";
}

} // namespace slither

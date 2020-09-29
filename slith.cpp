#include "slith.h"

namespace slither {

// multipoint_t slith::getPoints() const { return points; }

// void slith::setPoints(const multipoint_t &value) { points = value; }

slith::slith() : points{{0, 0}}, head_position(0, 0) {}

point_t slith::headpos() const { return head_position; }

void slith::chop_tail() {
  auto v = segments.back();
  segment_idx.remove(v);
  segments.pop_back();

  points.pop_back();
}

void slith::move(std::pair<int, int> d) { move(d.first, d.second); }

void slith::move(int dx, int dy) {
  point_t newhead{head_position.get<0>() + dx, head_position.get<1>() + dy};
  segment_t newsegment{newhead, head_position};
  geo_segment_index_value_t indexedsegment = segment_idx.add(newsegment);
  points.insert(points.begin(), newhead);
  segments.push_front(indexedsegment);
  head_position = newhead;
}

void slith::moveleft() { move(LEFT); }

void slith::moveright() { move(RIGHT); }

void slith::moveup() { move(UP); }

void slith::movedown() { move(DOWN); }

void slith::tick() { move(direction(currentDirection)); }

int slith::length() const { return points.size(); }
} // namespace slither

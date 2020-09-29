#include "point_indexer.h"

// geo_point_index_value_t point_indexer::add_point(point_t p) {
//  geo_point_index_value_t v{p, ++next_idx};
//  idx.insert(v);
//  return v;
//}

// vector<geo_point_index_value_t> point_indexer::intersects(box_t box) {
//  vector<geo_point_index_value_t> res;
//  idx.query(geoi::intersects(box), std::back_inserter(res));
//  return res;
//}

std::ostream &operator<<(std::ostream &os, const point_t &p) {
  return os << "(" << p.get<0>() << ", " << p.get<1>() << ")";
}

// std::ostream &operator<<(std::ostream &os, const multipoint_t &p) {
//  os << "{";
//  bool first = true;
//  for (auto &pnt : p) {
//    if (first) {
//      first = false;
//      os << pnt;
//    } else {
//      os << ", " << pnt;
//    }
//  }
//  return os << "}";
//}

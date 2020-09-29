#ifndef SLITH_NODE_H
#define SLITH_NODE_H

#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

using std::vector;

namespace geo = boost::geometry;
namespace geoi = geo::index;

namespace slither {

typedef geo::model::point<int, 2, geo::cs::cartesian> point_t;
typedef geo::model::box<point_t> box_t;
typedef geo::model::segment<point_t> segment_t;
typedef std::pair<box_t, int> geo_box_index_value_t;
typedef std::pair<point_t, int> geo_point_index_value_t;

// geoi::rtree<geo_index_value_t, geoi::quadratic<16>> s_rtree;

class slith_node {
  point_t position_;

public:
  explicit slith_node(const point_t &pos);
  point_t position() const;
  void setPosition(const point_t &position);
};
} // namespace slither

#endif // SLITH_NODE_H

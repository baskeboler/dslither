#ifndef POINT_INDEXER_H
#define POINT_INDEXER_H

#include <ostream>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/io/io.hpp>

using std::vector;

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)
BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

namespace geo = boost::geometry;
namespace geoi = geo::index;

typedef geo::model::point<int, 2, geo::cs::cartesian> point_t;
typedef geo::model::box<point_t> box_t;
typedef geo::model::segment<point_t> segment_t;
// typedef geo::model::multi_point<point_t> multipoint_t;
typedef geo::model::linestring<point_t> linestring_t;

typedef std::pair<box_t, int> geo_box_index_value_t;
typedef std::pair<point_t, int> geo_point_index_value_t;
typedef std::pair<segment_t, int> geo_segment_index_value_t;
typedef std::pair<linestring_t, int> geo_linestring_index_value_t;

template <typename Element> class geoindexer {
  int next_idx = 0;
  typedef std::pair<Element, int> value_t;
  geoi::rtree<value_t, geoi::quadratic<16>> idx;

public:
  value_t add(Element e) {
    value_t v{e, ++next_idx};
    idx.insert(v);
    return v;
  }

  template <typename Element2> vector<value_t> intersects(Element2 e) {
    vector<value_t> res;
    idx.query(geoi::intersects(e), std::back_inserter(res));
    return res;
  }
  vector<value_t> all() { return vector<value_t>(idx.begin(), idx.end()); }
  void remove(value_t v) { idx.remove(v); }
};

typedef geoindexer<box_t> box_indexer;
typedef geoindexer<segment_t> segment_indexer;
typedef geoindexer<point_t> point_indexer;
typedef geoindexer<linestring_t> linestring_indexer;
// typedef geoindexer<multipoint_t> multipoint_indexer;

// class point_indexer {
//  int next_idx = 0;
//  geoi::rtree<geo_point_index_value_t, geoi::rstar<16>> idx;

// public:
//  geo_point_index_value_t add_point(point_t p);

//  vector<geo_point_index_value_t> intersects(box_t box);
//};
extern std::ostream &operator<<(std::ostream &os, const point_t &p);
// extern std::ostream &operator<<(std::ostream &os, const multipoint_t &p);
#endif // POINT_INDEXER_H

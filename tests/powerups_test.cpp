#include <catch2/catch.hpp>

#include <fstream>
#include <iostream>
#include <ostream>
#include <tuple>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/io/io.hpp>

#include "point_indexer.h"

#include "powerup.h"
#include "powerup_manager.h"

using namespace slither;

TEST_CASE("create powerups", "[powerups]") {
  powerup_manager mgr;

  for (int i = 0; i < 20; i++) {
    mgr.random_powerup();
  }

  auto ps = mgr.all();
  for (const auto &p : ps) {
    std::cout << "powerup: " << p.getPosition().first << std::endl;
  }

  REQUIRE(ps.size() == 20);

  SECTION("write svg") {
    std::ofstream svg("my_map.svg");
    boost::geometry::svg_mapper<point_t> mapper(svg, 300, 300);
    for (const auto &p : ps) {
      mapper.add(p.getPosition().first);
    }
    for (const auto &p : ps) {
      mapper.map(p.getPosition().first, "fill-opacity:0.3;fill:rgb(51,51,153);"
                                        "stroke:rgb(51,51,153);stroke-width:2");
    }
  }
}

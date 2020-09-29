#include <catch2/catch.hpp>

#include <iostream>
#include <tuple>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/io/io.hpp>

#include <boost/tuple/tuple.hpp>

#include "../point_indexer.h"
#include "../slith.h"
#include "../slith_node.h"

TEST_CASE("1 + 1 = 2", "[placeholder]") { REQUIRE(2 == 1 + 1); }

TEST_CASE("create slith node", "[slith]") {
  using namespace slither;
  slith_node n{{1, 3}}, m{{1, 3}};

  REQUIRE(n.position().get<0>() == m.position().get<0>());
  REQUIRE(n.position().get<1>() == m.position().get<1>());
  REQUIRE(n.position().get<0>() == 1);
  REQUIRE(n.position().get<1>() == 3);
}

TEST_CASE("create slith", "[slith]") {
  using slither::slith;
  slith s;
  s.moveright();
  s.moveright();
  s.moveright();

  REQUIRE(s.length() == 4);

  SECTION("chop tail") {
    s.chop_tail();
    REQUIRE(s.length() == 3);
    //    std::cout << "slith points: " << s.getPoints() << std::endl;
  }
  SECTION("zigzag") {
    s.chop_tail();
    s.moveup();
    s.chop_tail();
    s.moveleft();
    s.chop_tail();
    s.moveup();
    s.chop_tail();
    s.moveright();
    s.chop_tail();

    //    std::cout << "slith points: " << s.getPoints() << std::endl;
  }
}

TEST_CASE("use point indexe", "[points]") {
  point_indexer idx;
  idx.add({1, 3});
  //  idx.add({5, 5});
  //  idx.add({-2, -2});
  //  std::cout << a.first. << ", " << a.second << std::endl;
  for (int i = -100; i <= 100; ++i) {
    idx.add({i, i});
  }
  SECTION("intersect just one") {

    box_t b{{4, 4}, {6, 6}};

    auto res = idx.intersects(b);

    REQUIRE(res.size() == 3);
    for (const auto &v : res) {
      std::cout << v.first << " returned" << std::endl;
    }
  }

  SECTION("intersect all") {

    box_t b{{-4, -4}, {6, 6}};

    auto res = idx.intersects(b);

    REQUIRE(res.size() == 12);
    for (const auto &v : res) {
      std::cout << v.first << " returned" << std::endl;
    }
  }
}

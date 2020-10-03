#include <catch2/catch.hpp>

#include <algorithm>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/io/io.hpp>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <boost/tuple/tuple.hpp>

#include "../player.h"
#include "../point_indexer.h"
#include "../slith.h"
#include "../slith_node.h"

using namespace slither;

TEST_CASE("create slith node", "[slith]") {
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
  for (int i = -100; i <= 10; ++i) {
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

TEST_CASE("primitive tests", "c++") {

  std::pair<int, int> p1{2, 3}, p2{3, 2}, p3{3, 3}, p4{2, 3};
  REQUIRE(p1 != p2);
  REQUIRE(p1 != p3);
  REQUIRE(p1 == p4);
  REQUIRE(p4 == p1);
  REQUIRE(p2 != p1);
}

TEST_CASE("pair maps tests", "c++") {

  typedef std::map<std::pair<int, int>, std::string> stringposmap;
  std::pair<int, int> p1{2, 3}, p2{3, 2}, p3{3, 3}, p4{2, 3};
  stringposmap themap;

  themap[p1] = "hello";
  themap[p2] = "world";

  SECTION("predicates") {

    REQUIRE(themap[p1] == "hello");
    REQUIRE(themap.contains(p1));
    REQUIRE(themap.contains(p2));
    REQUIRE(themap.contains(p4));
    REQUIRE(themap[p1] != themap[p2]);
    REQUIRE(!themap.contains(p3));
  }

  SECTION("the keys") {
    REQUIRE(themap.size() == 2);
    std::vector<std::pair<int, int>> keys;

    std::transform(themap.begin(), themap.end(),
                   std::back_insert_iterator(keys),
                   [](const std::pair<std::pair<int, int>, std::string> &p) {
                     return p.first;
                   });

    std::set<std::pair<int, int>> s{keys.begin(), keys.end()};
    REQUIRE(s == std::set<std::pair<int, int>>{p1, p2});
  }
}

TEST_CASE("players", "players") {
  slither::player p;
  p.setName("victor");
  p.setSlith(std::make_shared<slither::slith>());

  std::cout << "player: " << p << std::endl;
}
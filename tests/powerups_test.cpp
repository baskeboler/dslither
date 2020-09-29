#include <catch2/catch.hpp>

#include <iostream>
#include <tuple>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/io/io.hpp>

#include "../point_indexer.h"

#include "../powerup.h"
#include "../powerup_manager.h"

TEST_CASE("create powerups", "[powerups]") {
  powerup_manager mgr;

  for (int i = 0; i < 2000; i++) {
    mgr.random_powerup();
  }

  auto ps = mgr.all();

  for (const auto &p : ps) {
    std::cout << "powerup: " << p.getPosition().first << std::endl;
  }

  REQUIRE(ps.size() == 2000);
}

#include <catch2/catch.hpp>

#include "../color.h"

TEST_CASE("create color", "colors") {

  color_rgba c{0xFFFFFFFF};

  REQUIRE(c.r() == 0xFF);
  REQUIRE(c.g() == 0xFF);
  REQUIRE(c.b() == 0xFF);
  REQUIRE(c.a() == 0xFF);

  c.setR(0x0F);
  REQUIRE(c.r() == 0x0F);

  c.setG(0x0F);
  REQUIRE(c.g() == 0x0F);

  c.setB(0x0F);
  REQUIRE(c.b() == 0x0F);

  c.setA(0x0F);
  REQUIRE(c.a() == 0x0F);

  color_rgba comp{0x0F0F0F0F};
  REQUIRE(c == 0x0F0F0F0F);
}

TEST_CASE("add colors", "colors") {

  color_rgba red{0xFF0000FF}, green{0x00FF00FF}, blue{0x0000FFFF},
      black{0x000000FF}, white{0xFFFFFFFF};

  REQUIRE(red.r() == 0xFF);
  REQUIRE(red.g() == 0x00);
  REQUIRE(red.b() == 0x00);
  REQUIRE(red.a() == 0xFF);

  REQUIRE(red + green + blue == white);

  REQUIRE(red.css() == "#ff0000ff");
}
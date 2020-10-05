#include "url.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <regex>
#include <vector>

TEST_CASE("create http url", "http") {

  slither::net::url u{"google.com", slither::net::HTTP, 8080};

  REQUIRE(u.str() == "http://google.com:8080");
}

TEST_CASE("create https url", "https") {

  slither::net::url u{"google.com", slither::net::HTTPS, 8080};

  REQUIRE(u.str() == "https://google.com:8080");
}

TEST_CASE("create url with query params", "http") {

  slither::net::url u{"google.com",
                      slither::net::HTTP,
                      80,
                      "/endpoint",
                      {{"param1", "value1"}, {"somenumber", "234"}}};

  REQUIRE(u.str() == "http://google.com/endpoint?param1=value1&somenumber=234");
}

TEST_CASE("parse url ", "url") {
  std::regex r{"([a-z]{1,2}tps?)://((?:(?!(?:/|#|\\?|&)).)+)(?:(/(?:(?:(?:(?"
               "!(?:#|\\?|&)).)+/))?))?(?:((?:(?!(?:.|$|\\?|#)).)+))?(?:(.(?:("
               "?!(?:\\?|$|#)).)+))?(?:(\\?(?:(?!(?:$|#)).)+))?(?:(#.+))?"};

  std::vector<std::string> urls = {"http://google.com/the/path?a=12&b=puto",
                                   "https://www.google.com",
                                   "http://localhost:1234",
                                   "https://www.zentility.com/v1/customers/123/"
                                   "org/43242/index.html?force=true#theanchor"};

  for (const auto &u : urls) {

    std::cout << std::regex_match(u, r) << std::endl;

    std::smatch basematch;

    std::regex_match(u, basematch, r);

    std::cout << basematch.size() << " ";
    for (const auto &sm : basematch) {
      std::cout << sm << std::endl;
    }

    slither::net::url theurl = slither::net::url::parse(u);
    std::cout << theurl << std::endl;
  }
}
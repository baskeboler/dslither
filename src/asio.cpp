#include "http_client.h"
#include "url.h"
#include <iostream>

int main(int, char **argv) {
  using namespace slither::net;
  http_client client{};
  url u{url::parse(argv[1])};

  std::cout << client.get_request(u) << std::endl;

  return 0;
}
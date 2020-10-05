#include "beast.h"
#include "net.h"
#include "url.h"
#include <iostream>

std::string http_get(const std::string &url_str) {
  using slither::net::url;

  url theurl = url::parse(url_str);
  beast::http::request<beast::http::empty_body> r;
  beast::http::response<beast::http::string_body> response;
  net::io_context ioc;
  tcp::resolver res{net::make_strand(ioc)};
  beast::tcp_stream stream{net::make_strand(ioc)};
  beast::flat_buffer buffer;

  r.version(11);
  r.method(beast::http::verb::get);

  r.target(theurl.path());
  r.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  r.set(http::field::host, theurl.host());
  auto results =
      res.resolve(theurl.host() + ":" + std::to_string(theurl.port()), "http");

  stream.connect(results);

  http::write(stream, r);

  http::read(stream, buffer, response);
  stream.socket().shutdown(tcp::socket::shutdown_both);
  stream.close();

  return response.body();
}

void print(const boost::system::error_code & /*e*/) {
  std::cout << "Hello, world!" << std::endl;
}

int main(int argc, char **argv) {
  std::cout << http_get(argv[1]) << std::endl;
  //  boost::asio::io_context io;

  //  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

  //  t.async_wait(&print);

  //  io.run();

  return 0;
}
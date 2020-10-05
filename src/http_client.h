#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "beast.h"
#include "net.h"
#include "url.h"

namespace slither {
namespace net {

template <typename ReqBody = http::empty_body,
          typename ResBody = http::string_body>
class http_client {
  //  using  response_value = ResBody::value_type;

  using request_t = beast::http::request<ReqBody>;
  using response_t = beast::http::response<ResBody>;
  using response_type = typename ResBody::value_type;
  request_t _request;
  response_t _response;
  boost::asio::io_context _ioc;
  tcp::resolver _resolver;
  beast::tcp_stream _stream;
  beast::flat_buffer _buffer;

public:
  http_client() : _resolver{_ioc}, _stream{_ioc} {}
  ~http_client() = default;
  response_type get_request(const url &u) {

    _request.version(11);
    _request.method(beast::http::verb::get);
    _request.target(u.path());
    _request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    _request.set(http::field::host, u.host());

    auto results = _resolver.resolve(u.host(), std::to_string(u.port()));

    _stream.connect(results);

    http::write(_stream, _request);

    http::read(_stream, _buffer, _response);
    _stream.socket().shutdown(tcp::socket::shutdown_both);
    _stream.close();
    return _response.body();
  }
};

} // namespace net
} // namespace slither

#endif // HTTP_CLIENT_H

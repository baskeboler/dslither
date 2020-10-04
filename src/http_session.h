#ifndef HTTP_SESSION_H
#define HTTP_SESSION_H
#include <cstdlib>
#include <memory>

#include <boost/optional.hpp>
#include <boost/smart_ptr.hpp>

#include "beast.h"
#include "net.h"
#include "shared_state.h"

/** Represents an established HTTP connection
 */
class http_session : public boost::enable_shared_from_this<http_session> {
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  boost::shared_ptr<shared_state> state_;

  // The parser is stored in an optional container so we can
  // construct it from scratch it at the beginning of each new message.
  boost::optional<http::request_parser<http::string_body>> parser_;

  struct send_lambda;

  void fail(beast::error_code ec, char const *what);
  void do_read();
  void on_read(beast::error_code ec, std::size_t);
  void on_write(beast::error_code ec, std::size_t, bool close);

public:
  http_session(tcp::socket &&socket,
               boost::shared_ptr<shared_state> const &state);

  void run();
};

#endif // HTTP_SESSION_H
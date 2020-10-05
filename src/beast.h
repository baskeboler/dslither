#ifndef BEAST_H
#define BEAST_H
#ifndef BOOST_ASIO_DISABLE_NOEXCEPT
#define BOOST_ASIO_DISABLE_NOEXCEPT
#endif

#include <boost/beast.hpp>

#include <boost/beast/ssl.hpp>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>

#endif // BEAST_H

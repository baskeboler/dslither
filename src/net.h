#ifndef NET_H
#define NET_H
#ifndef BOOST_ASIO_DISABLE_NOEXCEPT
#define BOOST_ASIO_DISABLE_NOEXCEPT
#endif

#include <boost/asio.hpp>

namespace net = boost::asio;      // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

#endif // NET_H

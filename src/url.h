#ifndef URL_H
#define URL_H
#include <map>
#include <ostream>
#include <string>

#include <boost/log/trivial.hpp>

namespace slither {
namespace net {

enum protocol_t { HTTP, HTTPS };
typedef std::map<std::string, std::string> query_map_t;

class url {

  std::string _host;
  protocol_t _protocol;
  unsigned int _port;
  std::string _path;
  query_map_t _query_params;
  std::string _anchor;

public:
  explicit url(const std::string &host, const protocol_t &p = HTTP,
               const unsigned int &port = 80, const std::string &path = "",
               const query_map_t &query = {}, const std::string &anchor = "");

  ~url() = default;

  std::string str() const;

  static url parse(const std::string &u);
  std::string host() const;
  void setHost(const std::string &host);
  protocol_t protocol() const;
  void setProtocol(const protocol_t &protocol);
  unsigned int port() const;
  void setPort(unsigned int port);
  std::string path() const;
  void setPath(const std::string &path);
  query_map_t query_params() const;
  void setQuery_params(const query_map_t &query_params);
  std::string anchor() const;
  void setAnchor(const std::string &anchor);

  friend std::ostream &operator<<(std::ostream &, const url &);
};

std::ostream &operator<<(std::ostream &, const url &);
} // namespace net
} // namespace slither

#endif // URL_H

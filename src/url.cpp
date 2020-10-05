#include "url.h"
#include <regex>
#include <sstream>

namespace slither {
namespace net {

std::string url::host() const { return _host; }

void url::setHost(const std::string &host) { _host = host; }

protocol_t url::protocol() const { return _protocol; }

void url::setProtocol(const protocol_t &protocol) { _protocol = protocol; }

unsigned int url::port() const { return _port; }

void url::setPort(unsigned int port) { _port = port; }

std::string url::path() const { return _path; }

void url::setPath(const std::string &path) { _path = path; }

query_map_t url::query_params() const { return _query_params; }

void url::setQuery_params(const query_map_t &query_params) {
  _query_params = query_params;
}

std::string url::anchor() const { return _anchor; }

void url::setAnchor(const std::string &anchor) { _anchor = anchor; }

url::url(const std::string &host, const protocol_t &p, const unsigned int &port,
         const std::string &path, const query_map_t &query,
         const std::string &anchor)
    : _host{host}, _protocol{p}, _port{port}, _path{path},
      _query_params{query}, _anchor{anchor} {}

std::string url::str() const {
  std::stringstream ss;
  if (_protocol == HTTP)
    ss << "http://";
  else if (_protocol == HTTPS)
    ss << "https://";
  ss << _host;
  if (_port != 80)
    ss << ":" << _port;
  ss << _path;
  if (!_query_params.empty()) {
    ss << "?";
    bool first = true;
    for (const auto &kv : _query_params) {
      if (!first) {
        ss << "&";
      } else {
        first = false;
      }
      ss << kv.first << "=" << kv.second;
    }
  }
  if (!_anchor.empty())
    ss << "#" << _anchor;
  return ss.str();
}

std::pair<std::string, std::string> parse_query_kv(const std::string &part) {
  BOOST_LOG_TRIVIAL(debug) << "parsing query part: " << part;
  auto splitpos = part.find("=");
  if (splitpos == std::string::npos)
    throw std::runtime_error("invalid query string part");
  auto k = part.substr(0, splitpos);
  auto v = part.substr(splitpos + 1);
  return std::make_pair(k, v);
}

url url::parse(const std::string &u) {
  using std::map;
  using std::string;

  std::regex r{"([a-z]{1,2}tps?)://((?:(?!(?:/|#|\\?|&)).)+)(?:(/(?:(?:(?:(?"
               "!(?:#|\\?|&)).)+/))?))?(?:((?:(?!(?:.|$|\\?|#)).)+))?(?:(.(?:("
               "?!(?:\\?|$|#)).)+))?(?:(\\?(?:(?!(?:$|#)).)+))?(?:(#.+))?"};

  bool matched = std::regex_match(u, r);

  if (!matched)
    throw std::runtime_error("invalid url format");

  std::smatch base_match;
  std::regex_match(u, base_match, r);

  protocol_t p = base_match[1] == "http" ? HTTP : HTTPS;

  std::string hostname = base_match[2];
  unsigned int port = 80;
  auto colonpos = hostname.find(":");
  if (colonpos != std::string::npos) {
    port = std::stoul(hostname.substr(colonpos + 1));
    hostname = hostname.substr(0, colonpos);
  }
  std::string path = base_match[3];
  path += base_match[4];
  path += base_match[5];

  std::string query_str = base_match[6];
  map<string, string> vars;
  if (!query_str.empty()) {
    query_str = query_str.substr(1);
    int start = 0;
    auto splitpos = query_str.find("&");
    auto part = query_str.substr(start, splitpos);
    while (!part.empty()) {
      auto kv = parse_query_kv(part);
      vars.insert(kv);
      if (splitpos == std::string::npos)
        break;
      start = splitpos + 1;
      splitpos = query_str.find("&", start);
      part = query_str.substr(start, splitpos);
    };
  }

  std::string anchor = base_match[7];
  if (!anchor.empty()) {
    anchor = anchor.substr(1);
  }

  return slither::net::url{hostname, p, port, path, vars, anchor};
}

std::ostream &operator<<(std::ostream &os, const url &u) {
  return os << u.str();
}

} // namespace net
} // namespace slither

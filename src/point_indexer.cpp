#include "point_indexer.h"

std::ostream &operator<<(std::ostream &os, const point_t &p) {
  return os << geo::svg(p, "");
}

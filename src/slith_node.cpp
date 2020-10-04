#include "slith_node.h"

namespace slither {

point_t slith_node::position() const { return position_; }

void slith_node::setPosition(const point_t &position) { position_ = position; }

slith_node::slith_node(const point_t &pos) : position_{pos} {}
} // namespace slither

#include "player.h"

#include <iostream>
#include <string>

#include <boost/uuid/uuid_io.hpp>
namespace slither {

boost::uuids::uuid player::id() const { return _id; }

void player::setId(const boost::uuids::uuid &id) { _id = id; }

std::string player::name() const { return _name; }

void player::setName(const std::string &name) { _name = name; }

std::shared_ptr<slither::slith> player::slith() const { return _slith; }

void player::setSlith(const std::shared_ptr<slither::slith> &s) {
  this->_slith = s;
}

int player::score() const { return _score; }

void player::setScore(int score) { _score = score; }

player::player() {
  boost::uuids::random_generator gen;
  _id = gen();
}
std::ostream &operator<<(std::ostream &os, const player &player) {
  const slither::slith &s = *(player.slith());
  return os << "player{"
            << "id=" << boost::uuids::to_string(player.id())
            << ", name=" << player.name() << ", slith=" << s << "}";
}
} // namespace slither

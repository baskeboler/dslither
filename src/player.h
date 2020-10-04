#ifndef PLAYER_H
#define PLAYER_H
#include "./slith.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <memory>
#include <ostream>
#include <string>

namespace slither {

class player {
  boost::uuids::uuid _id;
  std::string _name;
  std::shared_ptr<slither::slith> _slith;
  int _score;

public:
  player();

  point_t headPosition() const { return _slith->headpos(); }
  boost::uuids::uuid id() const;
  void setId(const boost::uuids::uuid &id);
  std::string name() const;
  void setName(const std::string &name);
  std::shared_ptr<slither::slith> slith() const;
  void setSlith(const std::shared_ptr<slither::slith> &s);
  int score() const;
  void setScore(int score);

  friend std::ostream &operator<<(std::ostream &os, const player &player);
};
std::ostream &operator<<(std::ostream &os, const player &player);
} // namespace slither

#endif // PLAYER_H

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <boost/uuid/uuid.hpp>
#include <tuple>
namespace slither {
using boost::uuids::uuid;
class gamestate {
  //    std::pair
  int width, height;
  uuid id;

public:
  gamestate();
};
} // namespace slither

#endif // GAMESTATE_H

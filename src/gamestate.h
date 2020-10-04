#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <boost/uuid/uuid.hpp>
#include <tuple>
namespace slither {
using boost::uuids::uuid;
class gamestate {
  //    std::pair
  uuid id;
  unsigned int width;
  unsigned int height;

public:
  gamestate(const uuid &id, const unsigned int &w, const unsigned int &h);
  gamestate(const unsigned int &w, const unsigned int &h);
  uuid getId() const;
  unsigned int getWidth() const;
  void setWidth(unsigned int value);
  unsigned int getHeight() const;
  void setHeight(unsigned int value);
};
} // namespace slither

#endif // GAMESTATE_H

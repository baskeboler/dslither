#include "gamestate.h"
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>

namespace slither {

uuid gamestate::getId() const { return id; }

unsigned int gamestate::getWidth() const { return width; }

void gamestate::setWidth(unsigned int value) { width = value; }

unsigned int gamestate::getHeight() const { return height; }

void gamestate::setHeight(unsigned int value) { height = value; }

gamestate::gamestate(const boost::uuids::uuid &id, const unsigned int &w,
                     const unsigned int &h)
    : id{id}, width{w}, height{h} {}

gamestate::gamestate(const unsigned int &w, const unsigned int &h)
    : gamestate{boost::uuids::random_generator{}(), w, h} {}

} // namespace slither

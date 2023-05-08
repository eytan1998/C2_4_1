#include "Ninja.hpp"

#include <utility>

#define OLD_NINJA_SPEED 8
#define OLD_NINJA_HP 150

class OldNinja : public Ninja {

public:
    OldNinja(string name, Point location): Ninja(std::move(name),OLD_NINJA_HP,location,OLD_NINJA_SPEED){};

};
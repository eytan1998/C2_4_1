#include "Ninja.hpp"

constexpr int YOUNG_NINJA_SPEED = 14;
constexpr int YOUNG_NINJA_HP = 100;


class YoungNinja : public Ninja {
public:
    YoungNinja(string name, Point location) : Ninja(std::move(name), YOUNG_NINJA_HP, location, YOUNG_NINJA_SPEED) {};
};
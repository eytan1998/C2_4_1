
#include "Ninja.hpp"

Ninja::Ninja(string name, int hit_points, Point location, int speed) : Character(std::move(name), hit_points, location),
                                                                       speed(speed) {}

void Ninja::move(Character *enemy) {
}

void Ninja::slash(Character *enemy) {

}

string Ninja::print() {
    return "";
}





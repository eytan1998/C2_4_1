
#include "Cowboy.hpp"

#include <utility>

Cowboy::Cowboy(string name, Point location) : Character(std::move(name), COWBOY_HP, location), boolet(COWBOY_BULLETS) {}

void Cowboy::shoot(Character *enemy) {

}

bool Cowboy::hasboolets() { return true; }

void Cowboy::reload() { }


string Cowboy::print() {
    return "";
}

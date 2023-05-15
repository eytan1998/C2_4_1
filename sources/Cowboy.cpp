
#include "Cowboy.hpp"

#include <utility>

Cowboy::Cowboy(string name, Point location) : Character(std::move(name), COWBOY_HP, location), boolet(COWBOY_BULLETS) {}

void Cowboy::shoot(Character *enemy) {
    //if dead / out of boolet
    if (!isAlive() || !hasboolets()) return;
    enemy->hit(COWBOY_DMG);
    boolet--;
}

bool Cowboy::hasboolets() { return boolet > 0; }

void Cowboy::reload() { boolet = COWBOY_BULLETS; }


string Cowboy::print() {
    return ""+(isAlive()?"name: C" + (getName()) + "\nhit points: " + to_string(hp) + "\n"
        :"name: (C" + (getName()) + ")\n") // if is dead print with ()
        + "location: " + getLocation().print();
}


#include "Ninja.hpp"

Ninja::Ninja(string name, int hit_points, Point location, int speed) : Character(std::move(name), hit_points, location),
                                                                       speed(speed) {}

void Ninja::move(Character *enemy) {
    setLocation(Point::moveTowards(getLocation(), enemy->getLocation(), speed));
}

void Ninja::slash(Character *enemy) {
    if (!isAlive() || getLocation().distance(enemy->getLocation()) >= 1) return;
    enemy->hit(NINJA_DMG);
}

string Ninja::print() {
    return "" + (isAlive() ? "name: N" + (getName()) + "\nhit points: " + to_string(hp) + "\n"
                           : "name: (N" + (getName()) + ")\n") // if is dead print with ()
           + "location: " + getLocation().print();
}





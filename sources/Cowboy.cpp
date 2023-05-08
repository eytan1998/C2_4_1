
#include "Cowboy.hpp"

Cowboy::Cowboy(string name, Point location) : Character(name, COWBOY_HP, location), boolet(COWBOY_BULLETS) {}

void Cowboy::shoot(Character *enemy) {
    //if dead / out of boolet
    if (!isAlive() || boolet <= 0)return;
    enemy->hit(COWBOY_DMG);
    boolet--;
}

bool Cowboy::hasboolets() { return boolet > 0; }

void Cowboy::reload() { boolet = 6; }

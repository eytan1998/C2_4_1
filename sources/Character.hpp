

#ifndef CHARACTER_H
#define CHARACTER_H

#include <utility>

#include "Point.hpp"

class Character {
    Point location;
    int hp;
    string name;
public:
    Character(string name, int hit_points, Point location) : name(std::move(name)), hp(hit_points), location(location) {}

    bool isAlive() const { return hp > 0; }

    double distance(Character *other) {
        return location.distance(other->location);
    }

    void hit(int dmg) {
        hp -= dmg;
    }

    string getName() {
        return name;
    }

    Point getLocation() {
        return location;
    }

    void print() {
        cout << "name: " << name << endl
             << "hit points: " << hp << endl
             << "location: " << location << endl
             << (isAlive() ? "Alive" : "Dead") << endl
             << "Type :" << name[0] << endl;
    }
};


#endif //CHARACTER_H

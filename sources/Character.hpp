

#ifndef CHARACTER_H
#define CHARACTER_H

#include <utility>
#include <string>

#include "Point.hpp"

class Character {
    Point location;
    string name;
protected:
    int hp;
public:
    Character(string name, int hit_points, Point location) : name(std::move(name)), hp(hit_points),
                                                             location(location) {
        if (hp <= 0)throw invalid_argument("cant create dead character");
    }

    bool isAlive() const { return hp > 0; }

    double distance(Character *other) {
        return location.distance(other->location);
    }

    void hit(int dmg) {
        if (dmg <= 0)return;
        //not need to kill him more
        if (isAlive()) {
            if (dmg > hp) hp = 0;
            else hp -= dmg;
        }
    }

    string getName() {
        return name;
    }

    Point getLocation() {
        return location;
    }

    void setLocation(Point newPoint) {
        location = newPoint;
    }

    virtual string print() { return ""; }
};


#endif //CHARACTER_H

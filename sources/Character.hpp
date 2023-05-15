

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

    }
    virtual ~Character() = default;
    bool isAlive() const {
        return 0;

    }

    double distance(Character *other) {
        return 0;

    }

    void hit(int dmg) {

    }

    string getName() {
        return name;
    }

    Point getLocation() {
        return location;
    }

    void setLocation(Point newPoint) {
    }

    virtual string print() { return ""; }
};


#endif //CHARACTER_H

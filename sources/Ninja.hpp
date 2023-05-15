
#ifndef NINJA_H
#define NINJA_H
#include <utility>

#include "Character.hpp"
constexpr int NINJA_DMG =  31;

class Ninja: public Character{
    int speed;
public:
    Ninja(string name, int hit_points,Point location,int speed);
    ~Ninja() override = default;

    virtual void move(Character * enemy);
    void slash(Character * enemy);
    string print() override;

};
#endif //NINJA_H

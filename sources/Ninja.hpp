
#ifndef NINJA_H
#define NINJA_H
#include <utility>

#include "Character.hpp"
#define NINJA_DMG 31

class Ninja: public Character{
    int speed;
public:
    Ninja(string name, int hit_points,Point location,int speed): Character(std::move(name),hit_points,location),speed(speed){}
    void move(Character * enemy){

    }
    void slash(Character * enemy){
        if (!isAlive() || getLocation().distance(enemy->getLocation())>=1) return;
        enemy->hit(NINJA_DMG);
    }
};
#endif //NINJA_H

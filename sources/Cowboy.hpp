
#ifndef COWBOY_H
#define COWBOY_H

#include "Character.hpp"

constexpr int COWBOY_DMG = 10;
constexpr int COWBOY_BULLETS = 6;
constexpr int COWBOY_HP = 110;

class Cowboy : public Character {
    int boolet;//TODO why not bullet
public:
    Cowboy(string name, Point location);

    void shoot(Character *enemy);

    bool hasboolets();

    void reload();

    string print() override;
};


#endif //COWBOY_H

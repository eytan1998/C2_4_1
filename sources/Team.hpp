
#ifndef TEAM_H
#define TEAM_H

#include "Point.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"

namespace ariel{}
class Team {
    Character* team[10];
public:
    explicit Team(Character * leader);
    ~Team();
    void add(Character * newCharacter);
    void attack(Team * enemy);
    int stillAlive();
    void print();

};


#endif //TEAM_H

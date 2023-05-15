
#ifndef TEAM_H
#define TEAM_H

#include "Point.hpp"
#include "Cowboy.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
constexpr int MAX_TEAM_SIZE = 10;

namespace ariel{}
class Team {
    Character* team[MAX_TEAM_SIZE] = {NULL};
    int leader;
    int index;
public:
    explicit Team(Character * leader);
    ~Team();
    void add(Character * newCharacter);
    void attack(Team * enemy);
    int stillAlive();
    void print();
    int findNearest();
};


#endif //TEAM_H

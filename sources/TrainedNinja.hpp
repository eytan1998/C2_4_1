#include "Ninja.hpp"

#define TRAINED_NINJA_SPEED 12
#define TRAINED_NINJA_HP 120

class TrainedNinja :public  Ninja {

public:
    TrainedNinja(string name, Point location): Ninja(std::move(name),TRAINED_NINJA_HP,location,TRAINED_NINJA_SPEED){};

};
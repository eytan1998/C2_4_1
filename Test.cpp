#include "doctest.h"

#include <stdexcept>
#include "sources/Team.hpp"

#define LOOPS_AMOUNT 20
using namespace std;

TEST_CASE("Point") {
    SUBCASE("constructor") {
        CHECK_NOTHROW(Point a(1, 2));
        CHECK_NOTHROW(Point a(1.0, 2));
        CHECK_NOTHROW(Point a(1.0, 2.0));
        CHECK_NOTHROW(Point a(-1, 2.0));
    }
    SUBCASE("distance") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            int x1 = (rand() % (999 - (-999) + 1)) + -999;
            int y1 = (rand() % (999 - (-999) + 1)) + -999;

            int x2 = (rand() % (999 - (-999) + 1)) + -999;
            int y2 = (rand() % (999 - (-999) + 1)) + -999;
            CHECK_EQ(Point(x1, y1).distance(Point(x2, y2)), sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        }

    }
    SUBCASE("print"){
        CHECK_NOTHROW(Point(0,0).print());
        CHECK_NOTHROW(Point(1.2,0).print());
        CHECK_NOTHROW(Point(2,-123).print());
        CHECK_NOTHROW(Point(123.12312,412.123).print());
    }
    SUBCASE("moveTowards"){
        Point::moveTowards(Point(1,1),Point(1,1),2);
    }
}
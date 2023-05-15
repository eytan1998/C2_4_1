#include "doctest.h"

#include <stdexcept>
#include "sources/Team.hpp"
#include <limits>

#define LOOPS_AMOUNT 20
using namespace std;

#define MAX_INT std::numeric_limits<int>::max()
#define MIN_INT std::numeric_limits<int>::min()

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
    SUBCASE("print") {
        CHECK_NOTHROW(Point(0, 0).print());
        CHECK_NOTHROW(Point(1.2, 0).print());
        CHECK_NOTHROW(Point(2, -123).print());
        CHECK_NOTHROW(Point(123.12312, 412.123).print());
    }
    SUBCASE("moveTowards") {
        //in place
        Point a = Point::moveTowards(Point(1, 1), Point(1, 1), 2);
        CHECK_EQ(a, Point(1, 1));
        //more distance than need
        Point b = Point::moveTowards(Point(1, 1), Point(3, 2), 10);
        CHECK_EQ(b, Point(3, 2));
        //exactly distance than need
        Point c = Point::moveTowards(Point(1.3, 5.2), Point(3, 2), Point(1.3, 5.2).distance(Point(3, 2)));
        CHECK_EQ(c, Point(3, 2));
        //less distance than need
        Point d = Point::moveTowards(Point(1.3, 5.2), Point(3, 2), Point(1.3, 5.2).distance(Point(3, 2)) - 0.001);
        CHECK_NE(d, Point(3, 2));

        //loop
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            Point a((rand() % (999 - (-999) + 1)) + -999, (rand() % (999 - (-999) + 1)) + -999);
            Point b((rand() % (999 - (-999) + 1)) + -999, (rand() % (999 - (-999) + 1)) + -999);

            int randDist = (rand() % (99 - (-99) + 1)) + -99;
            int realDist = a.distance(b);

            if (realDist < randDist)
                CHECK_EQ(Point::moveTowards(a, b, randDist), b);
            else
                CHECK_NE(Point::moveTowards(a, b, randDist), b);
        }
    }
}

TEST_CASE("Character") {
    SUBCASE("constructor") {
        CHECK_NOTHROW(Character("asd", 19284710, Point(1.312, 1.123)));
        CHECK_THROWS(Character("asd", 0, Point(1.312, 1.123)));
        CHECK_THROWS(Character("asd", -123123, Point(1.312, 1.123)));
    }
    SUBCASE("getName") {
        Character a("asd", 19284710, Point(1.312, 1.123));
        CHECK_EQ("asd", a.getName());
    }
    SUBCASE("getLocation") {
        Character a("asd", 19284710, Point(1.311231232, 1.123));
        CHECK_EQ(Point(1.311231232, 1.123), a.getLocation());
    }
    SUBCASE("isAlive") {
        Character a("asd", 10, Point(1.311231232, 1.123));
        CHECK(a.isAlive());
        a.hit(12312);
        CHECK_FALSE(a.isAlive());
    }
    SUBCASE("distance") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            int x1 = (rand() % (999 - (-999) + 1)) + -999;
            int y1 = (rand() % (999 - (-999) + 1)) + -999;

            int x2 = (rand() % (999 - (-999) + 1)) + -999;
            int y2 = (rand() % (999 - (-999) + 1)) + -999;
            Character a("asd", 10, Point(x1, y1));
            Character b("asd", 10, Point(x2, y2));
            CHECK_EQ(a.distance(&b), sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        }
    }
    SUBCASE("hit") {
        Character a("asd", 10, Point(1.311231232, 1.123));
        a.hit(1);
        CHECK(a.isAlive());
        a.hit(2);
        CHECK(a.isAlive());
        a.hit(2);
        CHECK(a.isAlive());
        a.hit(5);
        CHECK_FALSE(a.isAlive());
        //cant resurrect
        a.hit(-5);
        CHECK_FALSE(a.isAlive());

        //body can endure inf dmg
        Character b("asd", 10, Point(1.311231232, 1.123));
        b.hit(MAX_INT);
        CHECK_FALSE(b.isAlive());
        b.hit(MIN_INT);
        CHECK_FALSE(b.isAlive());

    }
}

TEST_CASE("cowboy") {
    SUBCASE("constructor") {
        CHECK_NOTHROW(Cowboy("asd", Point(1.312, 1.123)));
        CHECK_NOTHROW(Cowboy("asd", Point(1.312, 1.123)));
    }
    SUBCASE("getName") {
        Cowboy a("asd", Point(1.312, 1.123));
        CHECK_EQ("asd", a.getName());
    }
    SUBCASE("getLocation") {
        Cowboy a("asd", Point(1.312, 1.123));
        CHECK_EQ(Point(1.312, 1.123), a.getLocation());
    }
    SUBCASE("isAlive") {
        //start with 110
        Cowboy a("asd", Point(1.312, 1.123));
        CHECK(a.isAlive());
        a.hit(COWBOY_HP - 1);
        CHECK(a.isAlive());
        a.hit(1);
        CHECK_FALSE(a.isAlive());
    }
    SUBCASE("distance") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            int x1 = (rand() % (999 - (-999) + 1)) + -999;
            int y1 = (rand() % (999 - (-999) + 1)) + -999;

            int x2 = (rand() % (999 - (-999) + 1)) + -999;
            int y2 = (rand() % (999 - (-999) + 1)) + -999;
            Cowboy a("asd", Point(x1, y1));
            Cowboy b("asd", Point(x2, y2));
            CHECK_EQ(a.distance(&b), sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        }
    }
    SUBCASE("shoot") {

        Character enemy("enemy", COWBOY_DMG * 6 + 1, Point(MIN_INT, MIN_INT));
        Cowboy hero("hero", Point(MAX_INT, MAX_INT));

        for (int i = 0; i < COWBOY_BULLETS; ++i) {
            hero.shoot(&enemy);
            CHECK(enemy.isAlive());
        }
        //dont have ammo
        hero.shoot(&enemy);
        CHECK(enemy.isAlive());
        CHECK_FALSE(hero.hasboolets());

        //have ammo but dead
        hero.reload();
        CHECK(hero.hasboolets());
        hero.hit(COWBOY_HP);//dead
        hero.shoot(&enemy);
        CHECK(enemy.isAlive());
        CHECK(hero.hasboolets());


        Cowboy hero2("hero2", Point(MAX_INT, MAX_INT));
        //can shoot dead body-lose bullets
        for (int i = 0; i < COWBOY_BULLETS; ++i) {
            hero2.shoot(&enemy);
            CHECK_FALSE(enemy.isAlive());
        }
        CHECK_FALSE(hero2.hasboolets());

    }
    SUBCASE("hasboolets") {
        Character enemy("enemy", COWBOY_DMG * 6 + 1, Point(MIN_INT, MIN_INT));
        Cowboy hero("hero", Point(MAX_INT, MAX_INT));
        for (int i = 0; i < COWBOY_BULLETS; ++i) {
            CHECK(hero.hasboolets());
            hero.shoot(&enemy);
            CHECK(enemy.isAlive());
        }
        //run out after 6;
        hero.shoot(&enemy);
        CHECK(enemy.isAlive());
        CHECK_FALSE(hero.hasboolets());

    }
    SUBCASE("reload") {
        Character enemy("enemy", MAX_INT, Point(MIN_INT, MIN_INT));
        Cowboy hero("hero", Point(MAX_INT, MAX_INT));

        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            hero.shoot(&enemy);
            hero.reload();
            CHECK(hero.hasboolets());
        }
    }
}

TEST_CASE("young-ninja") {
    SUBCASE("constructor") {
        CHECK_NOTHROW(YoungNinja("asd", Point(1.312, 1.123)));
        CHECK_NOTHROW(YoungNinja("asd", Point(1.312, 1.123)));
    }
    SUBCASE("getName") {
        YoungNinja a("asd", Point(1.312, 1.123));
        CHECK_EQ("asd", a.getName());
    }
    SUBCASE("getLocation") {
        YoungNinja a("asd", Point(1.312, 1.123));
        CHECK_EQ(Point(1.312, 1.123), a.getLocation());
    }
    SUBCASE("isAlive") {
        //start with 100
        YoungNinja a("asd", Point(1.312, 1.123));
        CHECK(a.isAlive());
        a.hit(YOUNG_NINJA_HP - 1);
        CHECK(a.isAlive());
        a.hit(1);
        CHECK_FALSE(a.isAlive());
    }
    SUBCASE("distance") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            int x1 = (rand() % (999 - (-999) + 1)) + -999;
            int y1 = (rand() % (999 - (-999) + 1)) + -999;

            int x2 = (rand() % (999 - (-999) + 1)) + -999;
            int y2 = (rand() % (999 - (-999) + 1)) + -999;
            YoungNinja a("asd", Point(x1, y1));
            YoungNinja b("asd", Point(x2, y2));
            CHECK_EQ(a.distance(&b), sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        }
    }
    SUBCASE("move") {
        // speed = 14
        //in place
        YoungNinja a_hero("asd", Point(0, 0));
        Character a_enemy("asd", 1000, Point(0, 0));
        a_hero.move(&a_enemy);
        CHECK_EQ(a_hero.getLocation(), Point(0, 0));
        //more distance than need
        YoungNinja b_hero("asd", Point(0, 0));
        Character b_enemy("asd", 1000, Point(1, 1));
        b_hero.move(&b_enemy);
        CHECK_EQ(b_hero.getLocation(), Point(1, 1));
        //exactly distance than need
        YoungNinja c_hero("asd", Point(0, 0));
        Character c_enemy("asd", 1000, Point(YOUNG_NINJA_SPEED, 0));
        c_hero.move(&c_enemy);
        CHECK_EQ(c_hero.getLocation(), Point(YOUNG_NINJA_SPEED, 0));
        //less distance than need
        YoungNinja d_hero("asd", Point(0, 0));
        Character d_enemy("asd", 1000, Point(YOUNG_NINJA_SPEED, 0.00001));
        d_hero.move(&d_enemy);
        CHECK_NE(c_hero.getLocation(), Point(YOUNG_NINJA_SPEED, 0.00001));

        //loop
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            Point a((rand() % (9 - (-9) + 1)) + -9, (rand() % (9 - (-9) + 1)) + -9);
            Point b((rand() % (9 - (-9) + 1)) + -9, (rand() % (9 - (-9) + 1)) + -9);

            double realDist = a.distance(b);

            YoungNinja hero("asd", a);
            Character enemy("asd", 1000, b);
            hero.move(&enemy);
            if (realDist <= YOUNG_NINJA_SPEED)
                CHECK_EQ(hero.getLocation(), b);
            else
                CHECK_NE(hero.getLocation(), b);
        }
    }
    SUBCASE("slash") {

        Character enemy("enemy", NINJA_DMG + 1, Point(0, 0));
        YoungNinja hero("hero", Point(15, 0));

        //out of reach 15 meter
        hero.slash(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());

        //out of reach 1 meter
        hero.move(&enemy);
        hero.slash(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());

        //in reach, and check has 40 dmg
        hero.move(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());
        hero.slash(&enemy);
        CHECK_FALSE(enemy.isAlive());

        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            //can slash dead body
            hero.slash(&enemy);
            CHECK_FALSE(enemy.isAlive());
        }


        Character enemy2("enemy", NINJA_DMG, Point(0, 0));
        hero.hit(1000);//dead
        hero.slash(&enemy2);
        hero.slash(&enemy2);
        hero.slash(&enemy2);
        CHECK(enemy2.isAlive());//dont get dmg
    }
}

TEST_CASE("trained-ninja") {
    SUBCASE("constructor") {
        CHECK_NOTHROW(TrainedNinja("asd", Point(1.312, 1.123)));
        CHECK_NOTHROW(TrainedNinja("asd", Point(1.312, 1.123)));
    }
    SUBCASE("getName") {
        TrainedNinja a("asd", Point(1.312, 1.123));
        CHECK_EQ("asd", a.getName());
    }
    SUBCASE("getLocation") {
        TrainedNinja a("asd", Point(1.312, 1.123));
        CHECK_EQ(Point(1.312, 1.123), a.getLocation());
    }
    SUBCASE("isAlive") {
        //start with 120
        TrainedNinja a("asd", Point(1.312, 1.123));
        CHECK(a.isAlive());
        a.hit(TRAINED_NINJA_HP - 1);
        CHECK(a.isAlive());
        a.hit(1);
        CHECK_FALSE(a.isAlive());
    }
    SUBCASE("distance") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            int x1 = (rand() % (999 - (-999) + 1)) + -999;
            int y1 = (rand() % (999 - (-999) + 1)) + -999;

            int x2 = (rand() % (999 - (-999) + 1)) + -999;
            int y2 = (rand() % (999 - (-999) + 1)) + -999;
            TrainedNinja a("asd", Point(x1, y1));
            TrainedNinja b("asd", Point(x2, y2));
            CHECK_EQ(a.distance(&b), sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        }
    }
    SUBCASE("move") {
        // speed = 12
        //in place
        TrainedNinja a_hero("asd", Point(0, 0));
        Character a_enemy("asd", 1000, Point(0, 0));
        a_hero.move(&a_enemy);
        CHECK_EQ(a_hero.getLocation(), Point(0, 0));
        //more distance than need
        TrainedNinja b_hero("asd", Point(0, 0));
        Character b_enemy("asd", 1000, Point(1, 1));
        b_hero.move(&b_enemy);
        CHECK_EQ(b_hero.getLocation(), Point(1, 1));
        //exactly distance than need
        TrainedNinja c_hero("asd", Point(0, 0));
        Character c_enemy("asd", 1000, Point(TRAINED_NINJA_SPEED, 0));
        c_hero.move(&c_enemy);
        CHECK_EQ(c_hero.getLocation(), Point(TRAINED_NINJA_SPEED, 0));
        //less distance than need
        TrainedNinja d_hero("asd", Point(0, 0));
        Character d_enemy("asd", 1000, Point(TRAINED_NINJA_SPEED, 0.00001));
        d_hero.move(&d_enemy);
        CHECK_NE(c_hero.getLocation(), Point(TRAINED_NINJA_SPEED, 0.00001));
        CHECK_EQ(c_hero.getLocation(), Point(TRAINED_NINJA_SPEED, 0));

        //loop
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            Point a((rand() % (9 - (-9) + 1)) + -9, (rand() % (9 - (-9) + 1)) + -9);
            Point b((rand() % (9 - (-9) + 1)) + -9, (rand() % (9 - (-9) + 1)) + -9);

            double realDist = a.distance(b);

            TrainedNinja hero("asd", a);
            Character enemy("asd", 1000, b);
            hero.move(&enemy);
            if (realDist <= TRAINED_NINJA_SPEED)
                CHECK_EQ(hero.getLocation(), b);
            else
                CHECK_NE(hero.getLocation(), b);
        }
    }
    SUBCASE("slash") {

        Character enemy("enemy", NINJA_DMG+1, Point(0, 0));
        TrainedNinja hero("hero", Point(15, 0));

        //out of reach 15 meter
        hero.slash(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());

        //out of reach 1 meter
        hero.move(&enemy);
        hero.slash(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());

        //in reach, and check has 40 dmg
        hero.move(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());
        hero.slash(&enemy);
        CHECK_FALSE(enemy.isAlive());

        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            //can slash dead body
            hero.slash(&enemy);
            CHECK_FALSE(enemy.isAlive());
        }


        Character enemy2("enemy", NINJA_DMG, Point(0, 0));
        hero.hit(1000);//dead
        hero.slash(&enemy2);
        hero.slash(&enemy2);
        CHECK(enemy2.isAlive());//dont get dmg
    }
}

TEST_CASE("old-ninja") {
    SUBCASE("constructor") {
        CHECK_NOTHROW(OldNinja("asd", Point(1.312, 1.123)));
        CHECK_NOTHROW(OldNinja("asd", Point(1.312, 1.123)));
    }
    SUBCASE("getName") {
        OldNinja a("asd", Point(1.312, 1.123));
        CHECK_EQ("asd", a.getName());
    }
    SUBCASE("getLocation") {
        OldNinja a("asd", Point(1.312, 1.123));
        CHECK_EQ(Point(1.312, 1.123), a.getLocation());
    }
    SUBCASE("isAlive") {
        //start with 150
        OldNinja a("asd", Point(1.312, 1.123));
        CHECK(a.isAlive());
        a.hit(OLD_NINJA_HP - 1);
        CHECK(a.isAlive());
        a.hit(1);
        CHECK_FALSE(a.isAlive());
    }
    SUBCASE("distance") {
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            int x1 = (rand() % (999 - (-999) + 1)) + -999;
            int y1 = (rand() % (999 - (-999) + 1)) + -999;

            int x2 = (rand() % (999 - (-999) + 1)) + -999;
            int y2 = (rand() % (999 - (-999) + 1)) + -999;
            OldNinja a("asd", Point(x1, y1));
            OldNinja b("asd", Point(x2, y2));
            CHECK_EQ(a.distance(&b), sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
        }
    }
    SUBCASE("move") {
        // speed = 14
        //in place
        OldNinja a_hero("asd", Point(0, 0));
        Character a_enemy("asd", 1000, Point(0, 0));
        a_hero.move(&a_enemy);
        CHECK_EQ(a_hero.getLocation(), Point(0, 0));
        //more distance than need
        OldNinja b_hero("asd", Point(0, 0));
        Character b_enemy("asd", 1000, Point(1, 1));
        b_hero.move(&b_enemy);
        CHECK_EQ(b_hero.getLocation(), Point(1, 1));
        //exactly distance than need
        OldNinja c_hero("asd", Point(0, 0));
        Character c_enemy("asd", 1000, Point(OLD_NINJA_SPEED, 0));
        c_hero.move(&c_enemy);
        CHECK_EQ(c_hero.getLocation(), Point(OLD_NINJA_SPEED, 0));
        //less distance than need
        OldNinja d_hero("asd", Point(0, 0));
        Character d_enemy("asd", 1000, Point(OLD_NINJA_SPEED, 0.00001));
        d_hero.move(&d_enemy);
        CHECK_NE(c_hero.getLocation(), Point(OLD_NINJA_SPEED, 0.00001));
        CHECK_EQ(c_hero.getLocation(), Point(OLD_NINJA_SPEED, 0));

        //loop
        srand((unsigned) time(NULL));
        rand();
        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            Point a((rand() % (9 - (-9) + 1)) + -9, (rand() % (9 - (-9) + 1)) + -9);
            Point b((rand() % (9 - (-9) + 1)) + -9, (rand() % (9 - (-9) + 1)) + -9);

            double realDist = a.distance(b);

            OldNinja hero("asd", a);
            Character enemy("asd", 1000, b);
            hero.move(&enemy);
            if (realDist <= OLD_NINJA_SPEED)
                CHECK_EQ(hero.getLocation(), b);
            else
                CHECK_NE(hero.getLocation(), b);
        }
    }
    SUBCASE("slash") {

        Character enemy("enemy", NINJA_DMG+1, Point(0, 0));
        OldNinja hero("hero", Point(OLD_NINJA_SPEED + 1, 0));

        //out of reach 9 meter
        hero.slash(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());

        //out of reach 1 meter
        hero.move(&enemy);
        hero.slash(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());

        //in reach, and check has 40 dmg
        hero.move(&enemy);
        hero.slash(&enemy);
        CHECK(enemy.isAlive());
        hero.slash(&enemy);
        CHECK_FALSE(enemy.isAlive());

        for (int i = 0; i < LOOPS_AMOUNT; ++i) {
            //can slash dead body
            hero.slash(&enemy);
            CHECK_FALSE(enemy.isAlive());
        }


        Character enemy2("enemy", NINJA_DMG, Point(0, 0));
        hero.hit(1000);//dead
        hero.slash(&enemy2);
        hero.slash(&enemy2);
        CHECK(enemy2.isAlive());//dont get dmg
    }
}

TEST_CASE("Team") {
    SUBCASE("constructor") {
        Point a(32.3,44),b(1.3,3.5);
        Cowboy *tom = new Cowboy("Tom", a);
        YoungNinja *sushi1 = new YoungNinja("sushi", b);
        TrainedNinja *sushi2 = new TrainedNinja("sushi", b);
        OldNinja *sushi3 = new OldNinja("sushi", b);

        CHECK_NOTHROW(Team team_A(tom););
        CHECK_NOTHROW(Team team_A(sushi1););
        CHECK_NOTHROW(Team team_A(sushi2););
        CHECK_NOTHROW(Team team_A(sushi3););

    }
    SUBCASE("add") {
        Point a(32.3,44),b(1.3,3.5);
        Cowboy *tom = new Cowboy("Tom", a);
        YoungNinja *sushi1 = new YoungNinja("sushi", b);
        TrainedNinja *sushi2 = new TrainedNinja("sushi", b);
        OldNinja *sushi3 = new OldNinja("sushi", b);
        OldNinja *sushi4 = new OldNinja("sushi", b);
        OldNinja *sushi5 = new OldNinja("sushi", b);
        OldNinja *sushi6 = new OldNinja("sushi", b);
        OldNinja *sushi7 = new OldNinja("sushi", b);
        OldNinja *sushi8 = new OldNinja("sushi", b);
        OldNinja *sushi9= new OldNinja("sushi", b);
        OldNinja *sushi10= new OldNinja("sushi", b);

        Team team(tom);
        CHECK_EQ(team.stillAlive(),1);
        team.add(sushi1);
        team.add(sushi2);
        team.add(sushi3);
        CHECK_EQ(team.stillAlive(),4);
        //cant add twice
        CHECK_THROWS(team.add(tom));
        team.add(sushi4);
        team.add(sushi5);
        team.add(sushi6);
        team.add(sushi7);
        team.add(sushi8);
        team.add(sushi9);
        CHECK_EQ(team.stillAlive(),10);
        //cant add more than 10
        team.add(sushi10);
        CHECK_EQ(team.stillAlive(),10);
    }
    SUBCASE("attack") {
        Point a(32.3,44),b(1.3,3.5);
        Cowboy *tom = new Cowboy("Tom", a);
        YoungNinja *sushi1 = new YoungNinja("sushi", b);
        TrainedNinja *sushi2 = new TrainedNinja("sushi", b);
        OldNinja *sushi3 = new OldNinja("sushi", b);
        Team teamA(tom);
        teamA.add(sushi1);

        Team teamB(sushi2);
        teamB.add(sushi3);

        CHECK_EQ(teamB.stillAlive(),2);
        for (int i = 0; i < 10; ++i) {
            teamA.attack(&teamB);
        }
        CHECK_EQ(teamB.stillAlive(),0);


    }
    SUBCASE("stillAlive") {
        Point a(32.3,44),b(1.3,3.5);
        Cowboy *tom = new Cowboy("Tom", a);
        YoungNinja *sushi1 = new YoungNinja("sushi", b);
        TrainedNinja *sushi2 = new TrainedNinja("sushi", b);
        OldNinja *sushi3 = new OldNinja("sushi", b);
        OldNinja *sushi4 = new OldNinja("sushi", b);
        OldNinja *sushi5 = new OldNinja("sushi", b);
        OldNinja *sushi6 = new OldNinja("sushi", b);
        OldNinja *sushi7 = new OldNinja("sushi", b);
        OldNinja *sushi8 = new OldNinja("sushi", b);
        OldNinja *sushi9= new OldNinja("sushi", b);
        OldNinja *sushi10= new OldNinja("sushi", b);

        Team team(tom);
        CHECK_EQ(team.stillAlive(),1);
        team.add(sushi1);
        team.add(sushi2);
        team.add(sushi3);
        CHECK_EQ(team.stillAlive(),4);
        team.add(sushi4);
        team.add(sushi5);
        team.add(sushi6);
        team.add(sushi7);
        team.add(sushi8);
        team.add(sushi9);
        CHECK_EQ(team.stillAlive(),10);
        sushi9->hit(OLD_NINJA_HP);
        CHECK_EQ(team.stillAlive(),9);
        //cant add after one dead
        team.add(sushi10);

        sushi8->hit(OLD_NINJA_HP);
        CHECK_EQ(team.stillAlive(),8);
        sushi7->hit(OLD_NINJA_HP);
        CHECK_EQ(team.stillAlive(),7);
        sushi6->hit(OLD_NINJA_HP);
        CHECK_EQ(team.stillAlive(),6);

    }
}
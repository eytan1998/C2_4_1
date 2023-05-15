#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iostream>

using namespace std;
class Point {
    double a, b;
public:
    Point(double a,double b);
    double distance(Point other);
    string print();
    static Point moveTowards(Point src,Point dest,double distance);
    friend ostream &operator<<(ostream &output, const Point &point);
    friend bool operator==(const Point &pointA , const Point &pointB);
    friend bool operator!=(const Point &pointA , const Point &pointB);
};


#endif
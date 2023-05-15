
#include "Point.hpp"

Point::Point(double a_val, double b_val) : x(a_val), y(b_val) {}

double Point::distance(Point other) {
    return 0;
}

string Point::print() {
    return "";
}

Point Point::moveTowards(Point src, Point dest, double distance) {
    return Point(0,0);
}

ostream &operator<<(ostream &output, const Point &point) {
    return output;
}

bool operator==(const Point &pointA , const Point &pointB) {
    return true;
}

bool operator!=(const Point &pointA, const Point &pointB) {
    return !(pointA==pointB);
}

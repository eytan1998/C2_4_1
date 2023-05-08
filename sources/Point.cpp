
#include "Point.hpp"

Point::Point(double a, double b) : a(a), b(b) {}

double Point::distance(Point other) {
    return std::sqrt(pow(a - other.a, 2) + pow(b - other.b, 2));
}

void Point::print() {
    cout << "(" << a << "," << b << ")" << endl;
}

Point Point::moveTowards(Point src, Point dest, double distance) {
    double deltaX = dest.a - src.a;
    double deltaY = dest.b - src.b;

    double coeff = distance / src.distance(dest);
    if (coeff > 1)coeff = 1;

    return Point(src.a + coeff * deltaX, src.b + coeff * deltaY);
}

ostream &operator<<(ostream &output, const Point &point) {
    output << "(" << point.a << "," << point.b << ")";
    return output;
}

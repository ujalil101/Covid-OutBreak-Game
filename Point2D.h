#ifndef Point2D_h
#define Point2D_h
#include "Vector2D.h"
using namespace std;

class Vector2D;
class Point2D {
    public:
        double x;
        double y;
        Point2D();
        Point2D(double, double);
};
double GetDistanceBetween(Point2D p1, Point2D p2);
ostream& operator<<(ostream& out, Point2D p1);
Point2D operator+(Point2D p1, Vector2D v1);
Vector2D operator-(Point2D p1, Point2D p2);
#endif
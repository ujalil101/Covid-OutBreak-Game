#ifndef Vector2D_h
#define  Vector2D_h
#include <iostream>

using namespace std;
class Point2D;
class Vector2D {
    public:
        double x;
        double y;
        Vector2D();
        Vector2D(double in_x, double in_y);
};
Vector2D operator* (Vector2D v1, double d);
Vector2D  operator/ (Vector2D v1, double d);
ostream& operator<< (ostream& out, Vector2D p1);
#endif
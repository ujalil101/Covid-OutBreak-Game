#include <iostream>
#include <math.h>
#include "Vector2D.h"
using namespace std;

Vector2D::Vector2D() {
    x = 0;
    y = 0;
}
Vector2D::Vector2D(double in_x, double in_y){
        x = in_x;
        y = in_y;
}
Vector2D operator*(Vector2D v1, double d) {
    double x = v1.x * d;
    double y = v1.y * d;
    Vector2D * v2 = new Vector2D(x,y);
    return *v2;
}
Vector2D operator/(Vector2D v1, double d) {
    if (d == 0){
        Vector2D * v2 = new Vector2D(v1.x, v1.y);
        return * v2;
    }
    else{
        double x = v1.x / d;
        double y = v1.y / d;
        Vector2D * v2 = new Vector2D(x ,y);
        return *v2;
    }
}
ostream& operator<<(ostream& out, Vector2D v1) {
    out << "<" << v1.x << "," << v1.y << ">";
    return out;
}
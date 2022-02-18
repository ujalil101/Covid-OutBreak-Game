#include "Point2D.h"
#include <iostream>
#include <math.h>
using namespace std;

Point2D::Point2D (){
    x = 0;
    y = 0;
}
Point2D::Point2D(double in_x, double in_y){
    x = in_x;
    y = in_y;
}
double GetDistanceBetween(Point2D p1, Point2D p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
ostream& operator<<(ostream& out, Point2D p1){
    out << "(" << p1.x << "," << p1.y << ")";
    return out;
}
Point2D operator+(Point2D p1, Vector2D v1) {
    Point2D newPoint = Point2D();
    newPoint.x = p1.x + v1.x;
    newPoint.y = p1.y + v1.y;
    return newPoint;
}
Vector2D operator-(Point2D p1, Point2D p2) {
    Vector2D newVector = Vector2D();
    newVector.x = p1.x - p2.x;
    newVector.y = p1.y - p2.y;
    return newVector;
}
#ifndef Building_h
#define Building_h
#include <iostream>
#include "GameObject.h"

using namespace std;

class Building:public GameObject
{
private:
    unsigned int student_count;
public:
    Building();
    Building(char in_code, int in_id, Point2D in_loc);
    void AddOneStudent();
    void RemoveOneStudent();
    void ShowStatus();
    bool ShouldBeVisible();
};
#endif
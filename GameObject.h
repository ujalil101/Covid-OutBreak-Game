#ifndef GameObject_h
#define GameObject_h
#include "Point2D.h"

#include <iostream>
#include <math.h>
using namespace std;

class GameObject {
    public: 
        GameObject();
        GameObject(char in_code); 
        GameObject(Point2D in_loc, int in_id, char in_code);
        Point2D GetLocation(); 
        int GetId();
        char GetState();
        virtual void ShowStatus();
        virtual bool Update() = 0;
        virtual bool ShouldBeVisible() = 0;
        virtual ~GameObject();
        void DrawSelf(char* ptr);
    protected:
        Point2D location;
        int id_num;
        char display_code;
        char state; 
};
#endif
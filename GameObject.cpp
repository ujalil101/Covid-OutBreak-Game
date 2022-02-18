#include <iostream>
#include "GameObject.h"
using namespace std;

GameObject::GameObject(){
    display_code = ' ';
}
GameObject::GameObject(char in_code) {
    state = 0;
    display_code = in_code;
    id_num = 1;
    cout << "GameObject Constructed" << endl;
}
GameObject::GameObject(Point2D in_loc, int in_id, char in_code){
    state = 0;
    display_code = in_code;
    id_num = in_id;
    location = in_loc;
    cout << "GameObject constructed" << endl;
}
GameObject::~GameObject(){
    cout << "GameObject destructed" << endl;
}
Point2D GameObject::GetLocation(){
    return location;
}
char GameObject::GetState(){
    return state;
}
int GameObject::GetId(){
    return id_num;
}
void GameObject::ShowStatus(){
    cout << display_code << " " << id_num << " at " << location;
}
bool GameObject::Update(){
    return true;
}
void GameObject::DrawSelf(char* ptr) {
    *ptr= this -> display_code;
    *(ptr+1)= '0' + this -> id_num;
}
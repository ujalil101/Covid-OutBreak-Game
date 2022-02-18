#include <iostream>
#include "Building.h"
using namespace std; 

Building::Building() : GameObject('B') { 
    cout << "Building Default Constructed." << endl;
}
Building::Building(char in_code, int in_id, Point2D in_loc) : GameObject(in_loc, in_id, in_code) {
    display_code = in_code;
    id_num = in_id;
    location = in_loc;
    cout << "Building Constructed." << endl;
}
void Building::AddOneStudent(){
    student_count +=1;
}
void Building::RemoveOneStudent() {
    student_count -=1;
}
void Building::ShowStatus() {
    cout<<display_code<<id_num<<" located at "<<location<<"\n";
    if(student_count == 1)
        cout << "\t " << student_count << " student is in this building." << endl;
    else if (student_count > 1)
        cout << "\t " << student_count << " students are in this building." << endl;
}
bool Building::ShouldBeVisible() {
    return true;
} 
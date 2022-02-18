#include "Virus.h"
#include <list>
#include <random>
#include "math.h"

Virus::Virus(string name, int id, Point2D in_loc) : GameObject(in_loc, id, 'V'), name(name){
    state = IN_ENVIRONMENT;
    cout<< "Virus Default Constructed" << endl;
}
 Virus::Virus(string name, double virulence, double resistance, double energy, bool variant, int id, Point2D in_loc):GameObject(in_loc, id, 'V'), name(name), virulence(virulence), resistance(resistance), energy(energy), variant(variant) {
    state = IN_ENVIRONMENT;
    cout<< "Virus Default Constructed" << endl;
}
Virus::~Virus() {
    cout << "Virus destructed" << endl;
}
string Virus::Name(){
    return name;
}
bool Virus::get_variant() {
    return variant;
}
double  Virus::get_virulence() {
    return virulence;
}
double  Virus::get_resistance() {
    return resistance;
}
double  Virus::get_energy() {
    return energy;
}
bool  Virus::get_in_student() {
    return is_in_student;
}
bool Virus::UpdateLocation(){
    switch (state){
        case IN_ENVIRONMENT: //causes virus to jump around 20 by 20 grid randonmly 
        {
            cout << display_code << id_num << ": step..." << endl;
            //found on cppreference.com 
            random_device _random; 
            default_random_engine r(_random()); //random number engine class that generates pseudo-random numbers.
            uniform_real_distribution <double> distance(-2, 2);  //Produces random num, uniformly distributed from [-2,2) that is, distributed according to the probability density function:
            while (true){
                Vector2D delta(distance(r), distance(r)); 
                location = location + delta;
                if (location.x >= 0 && location.x <= 20 && location.y >= 0 && location.y <= 20){   
                    if (energy >= 0)
                        energy = energy -  1.0 /(pow(resistance,2)); 
                    else{
                        state = DEAD;
                        energy = 0.0;
                    }
                    break;
                }
            }
            return true;
            break;
        }
        case IN_STUDENT: 
            location = (*current_student).GetLocation();
            if ((*current_student).IsInfected())
                state = IN_ENVIRONMENT;
            return true;
            break;
        case DEAD:
            return false;
            break;
    }
    return false;
}
void Virus::infect(Student *s){ 
    if (state == IN_ENVIRONMENT){
        state = IN_STUDENT;
        current_student = s;
        (*s).AddVirus(this);  
        cout << (*s).GetName() << " has been infected with " << name << "!" << endl;
    }
    else
        return;
}
bool Virus::Update(){
    if (IsAlive()){
        UpdateLocation();
        return false;
    }
    else {
        return true;
    }
    return false;
}
void Virus::ShowStatus(){
    cout << endl << name << " Status: ";
    GameObject::ShowStatus();
    switch (state){
        case IN_ENVIRONMENT:
            cout<<endl;
            break;
        case IN_STUDENT:
            cout << " in " << (*current_student).GetName() << endl;
            break;
        case DEAD:
            cout << " dead" << endl;
            break;
    }
    cout << "\tEnergy: " << energy << endl;
    cout << "\tVirulence: " << virulence << endl;
    cout << "\tResistance: " << resistance << endl;
}
bool Virus::IsAlive(){
    if (get_energy() > 0){
        return true;
    }
    else{
        return false;
    }
}
bool Virus::ShouldBeVisible(){
    if (state == DEAD){
        return false;
    }
    else
        return true;
}
void Virus::Apoptosis(){
    state = DEAD;
    energy = 0.0;
}
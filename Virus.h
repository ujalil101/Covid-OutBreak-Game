#ifndef Virus_h
#define Virus_h
#include <iostream>
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Building.h"
#include "Student.h"
using namespace std;

enum VirusStates{
    IN_ENVIRONMENT = 0,
    DEAD = 1,
    IN_STUDENT = 2
};
class Virus: public GameObject {
    protected:
        double virulence = 5.0;
        double resistance = 2.0;
        bool variant = false;
        double energy = 10.0;
        bool is_in_student = false;
        Student *current_student;
        double infection_treshold = 2.0;
        string name;
    public:
        Virus(string name, int id, Point2D in_loc);
        Virus(string name, double virulence, double resistance, double energy, bool variant, int id, Point2D in_loc);
        ~Virus();
        void infect(Student* s);
        string Name();
        void Apoptosis();
        bool get_variant();
        double get_virulence();
        double get_resistance();
        double get_energy();
        bool get_in_student();
        bool Update(); 
        void ShowStatus();
        bool IsAlive();
        bool ShouldBeVisible();
        bool UpdateLocation();
};
#endif

 

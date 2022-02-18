#ifndef Student_h
#define Student_h
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Building.h"
#include <list>
using namespace std;
class Virus;

enum StudentStates {
    STOPPED = 0,
    MOVING = 1,
    INFECTED = 2,
    AT_DOCTORS = 3,
    IN_CLASS = 4,
    MOVING_TO_DOCTOR = 5,
    MOVING_TO_CLASS = 6,
    STUDYING_IN_CLASS = 7,
    RECOVERING_ANTIBODIES = 8
};
class Student: public GameObject {
    public:
        Student();
        Student(char in_code);
        Student(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
        virtual ~Student();
        void AddVirus(Virus* virus);  
        void StartMoving(Point2D dest);
        void StartMovingToClass(ClassRoom* classr);
        void StartMovingToDoctor(DoctorsOffice* office);
        void StartLearning(unsigned int num_assignments);
        void StartRecoveringAntibodies(unsigned int num_vaccines);
        void Stop();
        string name;
        bool IsInfected();
        bool ShouldBeVisible();
        void ShowStatus();
        bool Update();
        string GetName(); 
    protected:
        bool UpdateLocation();
        void SetupDestination(Point2D dest);
    private:
        double speed;
        bool is_at_doctor;
        bool is_in_class;
        unsigned int antibodies;
        unsigned int credits;
        double dollars;
        unsigned int assignments_to_buy;
        unsigned int vaccines_to_buy;
        DoctorsOffice* current_office;
        ClassRoom* current_class;
        Point2D destination;
        Vector2D delta;
        list <pair <Virus*, double>> Viruses_Contracted;
};  
static double GetRandomAmountOfDollars();
#endif






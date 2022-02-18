#ifndef Model_h
#define Model_h
#include "GameObject.h"
#include "ClassRoom.h"
#include "DoctorsOffice.h"
#include "Student.h"
#include "View.h"
#include "Virus.h"
#include <list>
using namespace std; 

class Model {
    private:
        int time;
        list <DoctorsOffice*> office_ptrs;
        list <ClassRoom*> class_ptrs;
        list <Student*> student_ptrs;
        list <Virus*> virus_ptrs;
        list <GameObject*> object_ptrs;
        list <GameObject*> active_ptrs;
    public:
        Model();
        ~Model();
        Student* GetStudentPtr(int id);
        DoctorsOffice* GetDoctorsOfficePtr(int id);
        ClassRoom* GetClassRoomPtr(int id);
        Virus* GetVirusPtr(int id);
        bool Update();
        void Display(View& view);
        void ShowStatus();
        void AddNewMember(char chode, GameObject* object);
};
#endif
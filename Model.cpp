#include "Model.h"
#include "ClassRoom.h"
#include "DoctorsOffice.h"
#include "Student.h"
#include "Virus.h"
using namespace std;

Model::Model() {
    time = 0;
    Student *S1 = new Student(string("Homer"), 1, 'S', 2, Point2D(5, 1));
    Student *S2 = new Student(string("Marge"), 2, 'S', 1, Point2D(10, 1));
    Virus *V1 = new Virus(string("Virus1"), 5, 5, 25, false, 1, Point2D(20, 20));
    Virus *V2 = new Virus(string("Virus2"), 2, 1, 10, false, 2, Point2D(0, 12));
    DoctorsOffice *D1 = new DoctorsOffice(1, 1, 100, Point2D(1, 20));
    DoctorsOffice *D2 = new DoctorsOffice(2, 2, 200, Point2D(10, 20));
    ClassRoom *C1 = new ClassRoom(10, 1, 2.0, 3, 1, Point2D(0, 0));
    ClassRoom *C2 = new ClassRoom(20, 5, 7.5, 8, 2, Point2D(5, 5));
    object_ptrs = {S1, S2, D1, D2, C1, C2, V1, V2};
    active_ptrs = {S1, S2, D1, D2, C1, C2, V1, V2};
    office_ptrs = {D1, D2};
    class_ptrs = {C1, C2};
    student_ptrs = {S1, S2};
    virus_ptrs = {V1, V2};
    cout << "Model default constructed" << endl;
}
Model::~Model() {
    for (GameObject* &object : object_ptrs)
        delete object;
    cout << "Model destructed" << endl;
}
Student* Model::GetStudentPtr(int id){
    for (Student* &student : student_ptrs){
        if ((*student).GetId() == id){
            return student;
        }
    }
    return NULL;
}
DoctorsOffice* Model::GetDoctorsOfficePtr(int id){
    for (DoctorsOffice* &office : office_ptrs){
        if ((*office).GetId() == id){
            return office;
        }
    }
    return NULL;
}
ClassRoom* Model::GetClassRoomPtr(int id){
    for (ClassRoom* &classroom : class_ptrs){
        if ((*classroom).GetId() == id){
            return classroom;
        }
    }
    return NULL;
}
Virus* Model::GetVirusPtr(int id){
    for (Virus* &virus : virus_ptrs){
        if ((*virus).GetId() == id){
            return virus;
        }
    }
    return NULL;
}
bool Model::Update(){
    time++;
    bool diff, val = false;
    for (Student* &student : student_ptrs){ //if student is in virus then it gets infected
        for (Virus* &virus : virus_ptrs){
            if (GetDistanceBetween((*virus).GetLocation(), (*student).GetLocation()) <= 3 && !(*student).IsInfected())
                (*virus).infect(student);
        }
    }
    for (list <GameObject*>::iterator it = active_ptrs.begin(); it != active_ptrs.end(); it++){ //removes dead objects
        diff = (*it) -> Update(); 
        if (diff){
            val = true;
        }
        if (!((*it) -> ShouldBeVisible())) {
            it = active_ptrs.erase(it);
            cout << "Dead object removed" << endl;
        }
    }
    if (all_of(student_ptrs.begin(), student_ptrs.end(), [](Student* student) {return (*student).IsInfected();})){ //checks if all infected students and if so then GAMEOVER
        cout<<" _____   ___  ___  ___ _____   _____  _   _ ___________   "<<endl;
        cout<<"|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\ "<<endl;
        cout<<"| |  \\// /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ / "<<endl;
        cout<<"| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    /  "<<endl;
        cout<<"| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\  "<<endl;
        cout<<" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|  "<<endl;
        cout << endl << "You lose! All of your students are infected" << endl;
        exit(0);
    }
    if (all_of(class_ptrs.begin(), class_ptrs.end(), [](ClassRoom* classroom) {return (*classroom).passed();})){ //checks if all assignments are done and if so then GAMEOVER
        cout<<" _____   ___  ___  ___ _____   _____  _   _ ___________   "<<endl;
        cout<<"|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\ "<<endl;
        cout<<"| |  \\// /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ / "<<endl;
        cout<<"| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    /  "<<endl;
        cout<<"| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\  "<<endl;
        cout<<" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|  "<<endl;
        cout << "You win! All assigments done!" << endl;
        exit(0);
    }
    return val;
}
void Model::ShowStatus(){
    cout << endl << "Time: " << time << endl;
    for (GameObject* &object : object_ptrs)
        (*object).ShowStatus();
    return;
}
void Model::Display(View &view){
    view.Clear();
    cout << endl;
    for (GameObject* &object : active_ptrs){
        view.Plot(object);
    }
    view.Draw();
}
void Model::AddNewMember(char code, GameObject* object){
    object_ptrs.push_back(object);
    active_ptrs.push_back(object);
    switch (code){
        case 'd':
        {
            DoctorsOffice* new_office = dynamic_cast <DoctorsOffice*>(object);
            office_ptrs.push_back(new_office);
            break;
        }
        case 'c':
        {
            ClassRoom* new_classroom = dynamic_cast <ClassRoom*>(object);
            class_ptrs.push_back(new_classroom);
            break;
        }
        case 's':
        {
            Student* new_student = dynamic_cast <Student*>(object);
            student_ptrs.push_back(new_student);
            break;
        }
        case 'v':
        {
            Virus* new_virus = dynamic_cast <Virus*>(object);
            virus_ptrs.push_back(new_virus);
            break;
        }
    }
}
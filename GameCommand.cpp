#include "GameCommand.h"
#include "Input_Handling.h"

void GameCommand::DoMoveCommand(Model& model, int student_id, Point2D p1){
    if (model.GetStudentPtr(student_id) == 0){
        cout << "Error: Please enter a valid command!" << endl;
    }
    else{
        cout << "Moving " << model.GetStudentPtr(student_id)->GetId() << " to " << p1 << endl;
        model.GetStudentPtr(student_id)->StartMoving(p1);
    }
}
void GameCommand::DoMoveToDoctorCommand(Model& model, int student_id, int office_id){
    if ((model.GetDoctorsOfficePtr(office_id) == 0) || (model.GetStudentPtr(student_id) == 0)){
        cout << "Error: Please enter a valid command!" << endl;
    }
    else{
        model.GetStudentPtr(student_id)->StartMovingToDoctor(model.GetDoctorsOfficePtr(office_id));
        cout << "Moving " << model.GetStudentPtr(student_id)->GetId() << " to doctors office " << office_id << endl;
    }
}
void GameCommand::DoMoveToClassCommand(Model& model, int student_id, int class_id){
    if ((model.GetClassRoomPtr(class_id) == 0) && (model.GetStudentPtr(student_id) == 0)){
        cout << "Error: Please enter a valid command!" << endl;
    }
    else{
        model.GetStudentPtr(student_id)->StartMovingToClass(model.GetClassRoomPtr(class_id));
        cout << "Moving " << model.GetStudentPtr(student_id)->GetId() << " to class " << class_id << endl;
    }
}
void GameCommand::DoStopCommand(Model &model, int student_id){
    if (model.GetStudentPtr(student_id) == 0){
        cout << "Error: Please enter a valid command!" << endl;
    }
    else{
        model.GetStudentPtr(student_id)->Stop();
        cout << "Stopping " << model.GetStudentPtr(student_id)->GetId() << " " << student_id << endl;
    }
}
void GameCommand::DoLearningCommand(Model& model, int student_id, unsigned int assignments){
    if (model.GetStudentPtr(student_id) == 0){
        cout << "Error: Please enter a valid command!" << endl;
    }
    else{
        cout << "Teaching " << model.GetStudentPtr(student_id)->GetId() << endl;
        model.GetStudentPtr(student_id)->StartLearning(assignments);
    }
}
void GameCommand::DoRecoverInOfficeCommand(Model& model, int student_id, unsigned int vaccine_needs){
    if (model.GetStudentPtr(student_id) == 0){
        cout << "Error: Please enter a valid command!" << endl;
    }
    else{
        model.GetStudentPtr(student_id)->StartRecoveringAntibodies(vaccine_needs);
        cout << "Recovering " << model.GetStudentPtr(student_id)->GetId() << "'s antibodies" << endl;
    }
}
void GameCommand::DoGoCommand(Model& model, View& view){
    cout << "Advancing one tick." << endl;
    view.Clear();
    model.Update();
    model.ShowStatus();
    model.Display(view);
}
void GameCommand::DoRunCommand(Model& model, View& view){
    cout << "Advancing to next event." << endl;
    for (int i = 0; i <= 4; i+=1){
        view.Clear();
        bool updated = model.Update();
        if (updated)
            break;
    }
    model.ShowStatus();
    model.Display(view);
}
void GameCommand::NewCommand(Model &model, char code, int id, Point2D location){
    try{
        switch (code){
            case 'd':
                if (model.GetDoctorsOfficePtr(id) != NULL)
                    throw (Invalid_Input("DoctorsOffice with ID number " + to_string(id) + " already exists."));
                else{
                    DoctorsOffice *office = new DoctorsOffice(id, 1, 100, location);
                    model.AddNewMember(code, office);
                    break;
                }
            case 'c':
                if (model.GetClassRoomPtr(id) != NULL)
                    throw (Invalid_Input("ClassRoom with ID number " + to_string(id) + " already exists."));
                else{
                    ClassRoom *classroom = new ClassRoom(15, 5, 5, 4, id, location);
                    model.AddNewMember(code, classroom);
                    break;
                }
            case 's':
                if (model.GetStudentPtr(id) != NULL)
                    throw (Invalid_Input("Student with ID number " + to_string(id) + " already exists."));
                else{
                    Student *student = new Student("Student " + to_string(id), id, 'S', 5, location);
                    model.AddNewMember(code, student);
                    break;
                }
            case 'v':{
                if (model.GetVirusPtr(id) != NULL)
                    throw (Invalid_Input("Virus with ID number " + to_string(id) + " already exists."));
                else{
                    Virus *virus = new Virus("Virus " + to_string(id), 5, 5, 15, false, id, location);
                    model.AddNewMember(code, virus);
                    break;
                }
            }
            default:
                throw (Invalid_Input("Invalid type or the object with the selected ID already exists."));
        }
    }
    catch (Invalid_Input &except){
        cout << "Invalid input - " << except.x_ptr << endl;
    }
    return;
}
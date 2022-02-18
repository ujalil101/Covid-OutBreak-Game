#include "ClassRoom.h"
#include "DoctorsOffice.h"
#include "Student.h"
#include "Model.h"
#include "View.h"
#include "GameCommand.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "Input_Handling.h"
#include "Virus.h"
#include <sstream>
using namespace std;
int main(){
    cout << "EC327: Introduction to Software Engineering" << endl;
    cout << "Fall 2021" << endl;
    cout << "PA3" << endl;
    cout<<"\t\t_    _ _____ _     _____ ________  ___ _____   _____ _____ "<<endl;
    cout<<"\t\t| |  | |  ___| |   /  __ \\  _  |  \\/  ||  ___| |_   _|  _  |"<<endl;
    cout<<"\t\t| |  | | |__ | |   | /  \\/ | | | .  . || |__     | | | | | |"<<endl;
    cout<<"\t\t| |/\\| |  __|| |   | |   | | | | |\\/| ||  __|    | | | | | |"<<endl;
    cout<<"\t\t\\  /\\  / |___| |___| \\__/\\ \\_/ / |  | || |___    | | \\ \\_/ /"<<endl;
    cout<<"\t\t \\/  \\/\\____/\\_____/\\____/\\___/\\_|  |_/\\____/    \\_/  \\___/ "<<endl;
    cout<<"\t\t\t\t_____ _____  _   _ ___________ "<<endl;
    cout<<"\t\t\t\t/  __ \\  _  || | | |_   _|  _  \\ " <<endl;
    cout<<"\t\t\t\t| /  \\/ | | || | | | | | | | | |" <<endl;
    cout<<"\t\t\t\t| |   | | | || | | | | | | | | |" <<endl;
    cout<<"\t\t\t\t| \\__/\\ \\_/ /\\ \\_/ /_| |_| |/ / " <<endl;
    cout<<"\t\t\t\t\\____/ \\___/  \\___/ \\___/|___/  " <<endl;
    cout<<"\t\t\t_____ _   _ _________________ _____  ___   _   __ "<<endl;
    cout<<"\t\t\t|  _  | | | |_   _| ___ \\ ___ \\  ___|/ _ \\ | | / / "<<endl;
    cout<<"\t\t\t| | | | | | | | | | |_/ / |_/ / |__ / /_\\ \\| |/ /  "<<endl;
    cout<<"\t\t\t| | | | | | | | | | ___ \\    /|  __||  _  ||    \\  "<<endl;
    cout<<"\t\t\t\\ \\_/ / |_| | | | | |_/ / |\\ \\| |___| | | || |\\  \\ "<<endl;
    cout<<"\t\t\t \\___/ \\___/  \\_/ \\____/\\_| \\_\\____/\\_| |_/\\_| \\_/ "<<endl<<endl<<endl;
        char user_inp;
        int student_id;
        int object_id;
        string line;
        srand(time(NULL));
        Model model;
        View v;
        Point2D location;
        cout << endl;
        GameCommand G;
        model.ShowStatus();
        model.Display(v);
        do
        {
            cout << "Commands: " << endl;
            cout << "m ID x y " << endl;
            cout << "d ID1 ID2 " << endl;
            cout << "c ID1 ID2 " << endl;
            cout << "s ID " << endl;
            cout << "v ID vaccine_amount " << endl;
            cout << "a ID assignment_amount " << endl;
            cout<< "n TYPE ID X Y" <<endl;
            cout << "g " << endl;
            cout << "r " << endl;
            cout << "q " << endl;
            cout << endl;
            cout << endl << "Enter command: ";
            line.clear();
            try{
                getline(cin, line, '\n');
                istringstream inp(line);
                user_inp = line[0];
                switch(user_inp){
                    case 'm':{
                        inp >> user_inp >> student_id >> location.x >> location.y;
                        cout << endl;
                        G.DoMoveCommand(model, student_id, location);
                        cout << endl;
                        v.Draw();
                        break;
                    }
                    case 'd':{
                        int office_id;
                        inp >> user_inp >> student_id >> office_id;
                        cout << endl;
                        G.DoMoveToDoctorCommand(model, student_id, office_id);
                        cout << endl;
                        v.Draw();
                        break;
                    }
                    case 'c':{
                        int classroom_id;
                        inp >> user_inp >> student_id >> classroom_id;
                        cout << endl;
                        G.DoMoveToClassCommand(model, student_id, classroom_id);
                        cout << endl;
                        v.Draw();
                        break;
                    }
                    case 's': {
                        inp >> user_inp >> student_id;
                        cout << endl;
                        G.DoStopCommand(model, student_id);
                        cout << endl;
                        v.Draw();
                        break;
                    }
                    case 'v': {
                        int vaccine_amount;
                        inp >> user_inp >> student_id >> vaccine_amount; 
                        cout << endl;
                        G.DoRecoverInOfficeCommand(model, student_id, vaccine_amount);
                        v.Draw();
                        break;
                    }
                    case 'a':{
                        int assignment_amount;
                        inp >> user_inp >> student_id >> assignment_amount;
                        cout << endl;
                        G.DoLearningCommand(model, student_id, assignment_amount);
                        v.Draw();
                        break;
                    }
                    case 'n': {
                        char code;
                        inp >> user_inp >> code >> object_id >> location.x >> location.y;
                        cout << endl;
                        G.NewCommand(model, code, object_id, location);
                        cout << endl;
                        v.Draw();
                        break;
                    }
                    case 'g':
                        G.DoGoCommand(model, v);
                        break;
                    
                    case 'r':
                        G.DoRunCommand(model, v);
                        break;
                    case 'q':
                        cout << endl << "Program terminated" << endl << endl;
                        return 0;
                    default:
                        cout << "INVALID COMMAND" << endl;
                        break;		
                    }
                }
                catch (Invalid_Input& except){
                    cout << "Invalid Input" << except.x_ptr << endl; //catch statement for all exceptions
                }
        } while (true);
        return 0;
}
    
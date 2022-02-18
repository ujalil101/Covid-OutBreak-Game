#include "Student.h"
#include "Virus.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

// TODO: Pick sane default starting values
Student::Student() : GameObject('S') {
    antibodies = 20;
    dollars = 0.0;
    current_office = NULL;
    current_class = NULL;
    vaccines_to_buy = 0;
    assignments_to_buy = 0;
    speed = 1;
    this->name = "Student";
    is_at_doctor = false;
    is_in_class = false;
    credits = 0;
    this->speed = 5.0;
    cout << "Student constructed. " << endl;
}
Student::Student(string name, int id, char in_code, unsigned int speed, Point2D in_loc) : GameObject(in_loc, id, in_code) {
    antibodies = 20;
    dollars = 0.0;
    current_office = NULL;
    current_class = NULL;
    vaccines_to_buy = 0;
    assignments_to_buy = 0;
    this->name = name;
    this->speed = speed;
    is_at_doctor = false;
    is_in_class = false;
    credits = 0;
    cout << "Student constructed. " << endl;
}
Student::Student(char in_code) : GameObject(in_code) {
    antibodies = 20;
    dollars = 0.0;
    current_office = NULL;
    current_class = NULL;
    vaccines_to_buy = 0;
    assignments_to_buy = 0;
    this->name = name;
    this->speed = 5;
    is_at_doctor = false;
    is_in_class = false;
    credits = 0;
    cout << "Student constructed. " << endl;
}
Student::~Student() {
    cout << "Student destructed. " << endl;
}
// PA4 code goes here....
bool Student::IsInfected() {
    return antibodies == 0;
}
// returns true if the simulation should be stopped
bool Student::Update() {
    bool arrived = false;
    unsigned int vaccine_received = 0;
    unsigned int antibody_cost = 0;
	unsigned int antibody_boost = 0;
    double dollar_cost = 0;
    unsigned int num_assignments = 0;
    unsigned int credits_gain = 0;
    switch (state) {
        case STOPPED:
            return false;
        case MOVING:
            if (is_at_doctor) {
                current_office->RemoveOneStudent();
                is_at_doctor = false;
            } else if (is_in_class) {
                current_class->RemoveOneStudent();
                is_in_class = false;
            }
            if (antibodies == 0) {
                cout << name << " is out of antibodies and can't move." << endl;
                state = INFECTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = STOPPED;
                    return true;
                } else {
                    dollars += GetRandomAmountOfDollars();
                    antibodies -= 1;
                    return false;
                }
            }
        case MOVING_TO_CLASS:
            if (is_at_doctor) {
                current_office->RemoveOneStudent();
                is_at_doctor = false;
            } else if (is_in_class) {
                current_class->RemoveOneStudent();
                is_in_class = false;
            }
            if (antibodies== 0) {
                cout << name << " is out of antibodies and can't move." << endl;
                state = INFECTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = IN_CLASS;
                    is_in_class = true;
                    current_class->AddOneStudent();
                    return true;
                } else {
                    dollars += GetRandomAmountOfDollars();
                    antibodies -= 1;
                    return false;
                }
            }
        case MOVING_TO_DOCTOR:
            if (is_at_doctor) {
                current_office->RemoveOneStudent();
                is_at_doctor = false;
            } else if (is_in_class) {
                current_class->RemoveOneStudent();
                is_in_class = false;
            }
            if (antibodies == 0) {
                cout << name << " is out of antibodies and can't move." << endl;
                state = INFECTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = AT_DOCTORS;
                    is_at_doctor = true;
                    current_office->AddOneStudent();
                    return true;
                } else {
                    dollars += GetRandomAmountOfDollars();
                    antibodies -= 1;
                    return false;
                }
            }
        case RECOVERING_ANTIBODIES:
            dollar_cost = current_office->GetDollarCost(vaccines_to_buy);
            dollars -= dollar_cost;
            vaccine_received = current_office->DistributeVaccine(vaccines_to_buy);
			antibody_boost = (5 * vaccine_received);
			antibodies +=antibody_boost;
            cout << "** " << name << " bought " << vaccine_received << " vaccine(s)! **" << endl;
			cout << "** " << name << " recovered " << antibody_boost << " antibodies! **" << endl;
            vaccines_to_buy = 0;
            state = AT_DOCTORS;
            return true;
	   case STUDYING_IN_CLASS:
            antibody_cost = current_class->GetAntibodyCost(assignments_to_buy);
            dollar_cost = current_class->GetDollarCost(assignments_to_buy);
            credits_gain = current_class->TrainStudents(assignments_to_buy);
            antibodies -= antibody_cost;
            dollars -= dollar_cost;
            credits += credits_gain;
            cout << "** " << name << " completed " << assignments_to_buy << " assignment(s)! **" << endl;
            cout << "** " << name << " gained " << credits_gain << " credits! **" << endl;
            assignments_to_buy = 0;
            state = IN_CLASS;
            return true;
        case INFECTED:
        case IN_CLASS:
        case AT_DOCTORS:
        default:
            return false;
    }
}
void Student::StartMovingToDoctor(DoctorsOffice* office) {
    if (!IsInfected()) {
        if(this->location.x == office->GetLocation().x && this->location.y == office->GetLocation().y) {
            cout << display_code << GetId() << ": I am already at the Doctor's Office!" << endl;
        } else {
            if (is_at_doctor) {
                current_office->RemoveOneStudent(); // handles corner case
                is_at_doctor = false;
            } else if (is_in_class) {
                current_class->RemoveOneStudent();
                is_in_class = false;
            }
            state = MOVING_TO_DOCTOR;
            current_office = office;
            SetupDestination(office->GetLocation());
            cout << display_code << GetId() << ": On my way to doctor's " << office->GetId() << endl;
        }
    } else
        cout << display_code << GetId() << ": I am infected so should have gone to the doctor's..." << endl;
}
void Student::StartMovingToClass(ClassRoom* classr) {
    if (!IsInfected()) {
        if(this->location.x == classr->GetLocation().x && this->location.y == classr->GetLocation().y) {
            cout << display_code << GetId() << ": I am already at the Classroom!" << endl;
        } else {
            if (is_in_class) {
                current_class->RemoveOneStudent(); // handles corner case
                is_in_class = false;
            } else if (is_at_doctor) {
                current_office->RemoveOneStudent();
                is_at_doctor = false;
            }
            state = MOVING_TO_CLASS;
            current_class = classr;
            SetupDestination(classr->GetLocation());
            cout << display_code << GetId() << ": On my way to school " << classr->GetId() << endl;
        }
    } else
        cout << display_code << GetId() << ": I am infected so I can't move to class.." << endl;
}
void Student::StartLearning(unsigned int num_assignments) {
    unsigned int assignments_in_class = 0;
    if (!IsInfected()) {
        if (state == IN_CLASS || state == STUDYING_IN_CLASS) {
            if (current_class->IsAbleToLearn(num_assignments,
                                           dollars, antibodies)) {
                if (!current_class->passed()) {
                    assignments_in_class = current_class->GetNumAssignmentsRemaining();
                    assignments_to_buy = min(num_assignments, assignments_in_class);
                    state = STUDYING_IN_CLASS;
                    cout << display_code << GetId() << ": Started to learn with " << assignments_to_buy
                         << " assignments at Classroom " << current_class->GetId() << endl;
                } else
                    cout << display_code << GetId() << ": Cannot learn! This Classroom is already passed!"
                         << current_class->GetId() << endl;
            } else
                cout << display_code << GetId() << ": Not enough antibodies and/or money for school" << endl;
        } else
            cout << display_code << GetId() << ": I can only learn in a Classroom!" << endl;
    } else
        cout << display_code << GetId() << ": I am infected so no more school for me.." << endl;
}
void Student::StartRecoveringAntibodies(unsigned int num_vaccines) {
    unsigned int vaccine_count_in_office = 0;
    if (state == AT_DOCTORS || state == RECOVERING_ANTIBODIES) {
        if (IsInfected())
            cout << display_code << GetId() << ": I barely made it to the Doctor's Office!" << endl;
        if (current_office->CanAffordVaccine(num_vaccines, dollars)) {
            if (current_office->HasVaccine()) {
                vaccine_count_in_office = current_office->GetNumVaccineRemaining();
                state = RECOVERING_ANTIBODIES;
                vaccines_to_buy = min(num_vaccines, vaccine_count_in_office);
                cout << display_code << GetId() << ": Started recovering " << vaccines_to_buy
                     << " vaccine(s) at Doctor's Office " << current_office->GetId() << endl;
            } else
                cout << display_code << GetId()
                    << ": Cannot recover! No vaccine remaining in this Doctor's Office "
                     << current_office->GetId() << endl;
        } else
            cout << display_code << GetId() << ": Not enough money to buy vaccine." << endl;
    } else
        cout << display_code << GetId() << ": I can only recover antibodies at a Doctor's Office!" << endl;
}
void Student::StartMoving(Point2D dest) {
    if (!IsInfected()) {
        if (this->location.x == dest.x && this->location.y == dest.y) {
            cout << display_code << GetId() << ": I'm already there. see?" << endl;
        } else {
            state = MOVING;
            SetupDestination(dest);
            cout << display_code << GetId() << ": On my way." << endl;
        }
    } else {
        cout << display_code << GetId() << ": I am infected. I may move but you just cannot see me. " << endl;
    }
}
void Student::SetupDestination(Point2D dest) {
    destination = dest;
    delta = (destination - location)*(speed / GetDistanceBetween(destination, location));
}
void Student::Stop() {
    state = STOPPED;
    cout << display_code << GetId() << ": Stopping.." << endl;
}
bool Student::UpdateLocation() {
    //check if within one step
    if (fabs((destination - location).x) <= fabs(delta.x) &&
        fabs((destination - location).y) <= fabs(delta.y)) {
        location = destination;
        cout << display_code << GetId() << ": I’m there!" << endl;
        return true;
    }
    else {
        location = location + delta;
        cout << display_code << GetId() << ": step..." << endl;
       for (pair <Virus*, double> &virus : Viruses_Contracted){ //enhanced for loop
            double virulence = (*virus.first).get_virulence(); 
            double virus_resistance = (*virus.first).get_resistance();
            double student_resistance = virus.second;
            cout << student_resistance << " " << virulence << endl;
            if (student_resistance >= virulence)
                continue;
            else{
                antibodies -= ceil(0.5 * (virulence - student_resistance));
                virus.second += 0.5 + student_resistance/virus_resistance;
                if (antibodies <= 0){
                    antibodies = 0;
                    state = INFECTED;
                }
                if (virus.second >= virulence){
                    virus.second = virulence;
                    (*virus.first).Apoptosis();
                    cout << (*virus.first).Name() << " has been eliminated!" << endl;
                }   
            }
        }
        if (antibodies != 0)
            antibodies -= 1;
        dollars += GetRandomAmountOfDollars();
        return false;

    }
}
double GetRandomAmountOfDollars() {
    double f_min = 0.0;
    double f_max = 2.0;
    double f = (double)rand() / RAND_MAX;
    return f_min + f * (f_max - f_min);
}
void Student::ShowStatus() {
    cout << name << " status: ";
    GameObject::ShowStatus();
    switch (state) {
        case STOPPED:
            cout << " stopped" << endl;
            break;
        case MOVING:
            cout << " moving at a speed of " << speed
                 << " to " << destination << " at each step of " << delta << endl;
            break;
        case MOVING_TO_DOCTOR:
            cout << " heading to Doctor's Office " << current_office->GetId()
                 << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        case MOVING_TO_CLASS:
            cout << " heading to Classroom" << current_class->GetId()
                 << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        case IN_CLASS:
            cout << " inside Classroom " << current_class->GetId() << endl;
            break;
        case AT_DOCTORS:
            cout << " inside Doctor's Office " << current_office->GetId() << endl;
            break;
        case STUDYING_IN_CLASS:
            cout << " studying at Classroom " << current_class->GetId() << endl;
        case RECOVERING_ANTIBODIES:
            cout << " recovering antibodies in Doctor's Office " << current_office->GetId() << endl;
            break;
        case INFECTED:
            cout << " is infected!" << endl;
        default:
            break;
    }
    //  Print stats here
    cout << "\tAntibodies: " << antibodies << endl;
    cout << "\tDollars: " << dollars << endl;
    cout << "\tCredits: " << credits << endl;
}
bool Student::ShouldBeVisible() {
    return !IsInfected();
}
string Student::GetName(){
    return name;
}
void Student::AddVirus(Virus* virus){
    pair <Virus*, double> new_virus(virus, 0.0);
    Viruses_Contracted.push_back(new_virus);
}

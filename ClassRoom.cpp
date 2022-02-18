#include "ClassRoom.h"
using namespace std;

ClassRoom::ClassRoom() {
    display_code = 'C';
    state = NOT_PASSED;
    max_number_of_assignments = 10;
    num_assignments_remaining = 10;
    antibody_cost_per_assignment = 1;
    dollar_cost_per_assignment = 1.0;
    credits_per_assignment = 2;
    cout<< "ClassRoom default constructed."<<endl;
}
ClassRoom::~ClassRoom() {
    cout << "ClassRoom destructed" << endl;
}
ClassRoom::ClassRoom(unsigned int max_assign, unsigned int antibody_cost, double dollar_cost, unsigned int crd_per_assign, int in_id, Point2D in_loc) {
    display_code = 'C';
    state = NOT_PASSED;
    id_num = in_id;
    max_number_of_assignments = max_assign;
    num_assignments_remaining = max_assign;
    antibody_cost_per_assignment = antibody_cost;
    credits_per_assignment = crd_per_assign;
    dollar_cost_per_assignment = dollar_cost;
    location = in_loc;
    cout << "ClassRoom Constructed" <<endl;
}
double ClassRoom::GetDollarCost(unsigned int unit_qty) {
    return (dollar_cost_per_assignment * unit_qty);
}
unsigned int ClassRoom::GetAntibodyCost(unsigned int unit_qty) {
    return (antibody_cost_per_assignment * unit_qty);
}
unsigned int ClassRoom::GetNumAssignmentsRemaining() {
    return (num_assignments_remaining);
}
bool ClassRoom::IsAbleToLearn(unsigned int unit_qty, double budget, unsigned int antibodies){
    if(GetDollarCost(unit_qty) <= budget && GetAntibodyCost(unit_qty) <= antibodies)
        return true;
    else
        return false;
}
unsigned int ClassRoom::TrainStudents(unsigned int assignment_units) {
     if (assignment_units <= num_assignments_remaining){
        num_assignments_remaining -= assignment_units;
        return assignment_units * credits_per_assignment;
    }
    else{
        unsigned int credits_earned = num_assignments_remaining * credits_per_assignment;
        num_assignments_remaining = 0;
        return credits_earned;
    }
}
bool ClassRoom::Update() {
    if (num_assignments_remaining == 0 && state != PASSED){
        state = PASSED;
        display_code = 'c';
        cout << display_code << id_num << " has been passed" << endl;
        return true;
    }
    else
        return false;
}
bool ClassRoom::passed () {
    bool val = false;
	if(num_assignments_remaining == 0)
		val = true;
	return val;
}
void ClassRoom::ShowStatus() {
    cout << " " << endl;
	cout << "ClassRoom Status: ";
	Building::ShowStatus();
	cout << "\t Max Number of Assignments: " << max_number_of_assignments << endl;
	cout << "\t Antibody cost per assignment: " << antibody_cost_per_assignment << endl;
	cout << "\t Dollar per assignment: " << dollar_cost_per_assignment << endl;
	cout << "\t Credits per assignment: " << credits_per_assignment << endl;
	cout << "\t " << num_assignments_remaining << " assignment(s) are remaining for this ClassRoom."<<endl;
}

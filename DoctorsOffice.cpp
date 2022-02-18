#include "DoctorsOffice.h"

DoctorsOffice::DoctorsOffice() {
    display_code = 'D';
    vaccine_capacity = 100;
    num_vaccine_remaining = vaccine_capacity;
    dollar_cost_per_vaccine = 5;
    state = VACCINE_AVAILABLE;
    cout << "DoctorsOffice default constructed"<< endl;
}
DoctorsOffice::~DoctorsOffice() {
    cout << "DoctorsOffice destructed" << endl;
}
DoctorsOffice::DoctorsOffice (int in_id, double vaccine_cost, unsigned int vaccine_cap, Point2D in_loc) {
    display_code = 'D';
    id_num = in_id;
    location = in_loc;
    dollar_cost_per_vaccine = vaccine_cost;
    vaccine_capacity = vaccine_cap;
    num_vaccine_remaining = vaccine_capacity;
    state = VACCINE_AVAILABLE;
    cout << "DoctorsOffice constructed"<< endl;
} 
bool DoctorsOffice::HasVaccine() {
    if((num_vaccine_remaining >= 1 ))
        return true;
    else 
        return false;
}
unsigned int DoctorsOffice::GetNumVaccineRemaining() {
    return num_vaccine_remaining;
}
bool DoctorsOffice::CanAffordVaccine(unsigned int vaccine, double budget) {
    if (vaccine * dollar_cost_per_vaccine > budget)
        return false;
    else 
        return true;
}
double DoctorsOffice::GetDollarCost(unsigned int vaccine) {
    return ((dollar_cost_per_vaccine) * vaccine);
}
unsigned int DoctorsOffice::DistributeVaccine(unsigned int vaccine_needed) {
    unsigned int val = 0;
    if((num_vaccine_remaining) >= vaccine_needed){
        (num_vaccine_remaining) -= vaccine_needed;
	    val = vaccine_needed;
    }
    else {
        val = (num_vaccine_remaining);
        num_vaccine_remaining = 0;
    }
    return val;
}
bool DoctorsOffice::Update()   {
    if (!HasVaccine() && state == VACCINE_AVAILABLE){
        state = NO_VACCINE_AVAILABLE;
        display_code = 'd';
        cout << "DoctorsOffice " << id_num << " has ran out of vaccine." << endl;
        return true;
    }
    else
        return false;
}

void DoctorsOffice::ShowStatus() {
    cout << " " << endl;
    cout << "DoctorsOffice Status: ";
    Building::ShowStatus();
    cout << "\t Dollar per vaccine: " << dollar_cost_per_vaccine << endl;
    cout << "\t Has " << num_vaccine_remaining << " vaccine(s) remaining." << endl;
}
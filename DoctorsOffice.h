#ifndef DoctorsOffice_h
#define DoctorsOffice_h
#include "Building.h"

enum DoctorsOfficeStates {
    VACCINE_AVAILABLE = 0,
    NO_VACCINE_AVAILABLE = 1,
};

class DoctorsOffice : public Building 
{
    private: 
        unsigned int vaccine_capacity;
        unsigned int num_vaccine_remaining;
        double dollar_cost_per_vaccine;
    public:
        DoctorsOffice();
        virtual ~DoctorsOffice();
        DoctorsOffice (int in_id, double vaccine_cost, unsigned int vaccine_cap, Point2D in_loc);
        bool HasVaccine();
        unsigned int GetNumVaccineRemaining();
        bool CanAffordVaccine(unsigned int vaccine, double budget);
        double GetDollarCost(unsigned int vaccine);
        unsigned int DistributeVaccine(unsigned int vaccine_needed);
        bool Update();
        void ShowStatus();
};
#endif

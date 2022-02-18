#ifndef Input_Handling_h
#define Input_Handling_h
#include <string>
using namespace std;

class Invalid_Input
{
    public:
        string x_ptr;
        Invalid_Input(string in_ptr) : x_ptr(in_ptr) {}
    private:
        Invalid_Input();
};

#endif
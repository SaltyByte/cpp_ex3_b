#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    ifstream units_file{"myTestFile.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(-5,"kg");
    NumberWithUnits b(-4,"kg");
    NumberWithUnits c(1,"day");
    NumberWithUnits d(1440,"min");


    boolalpha(cout);
//    cout << (a >= b) << endl;
//    cout << (c > d) << endl;
//    cout << (c < d) << endl;
//    cout << (d > c) << endl;
//    cout << (d < c) << endl;

    NumberWithUnits temp_input(7, "kg");
    istringstream iss("20 [day]");
    iss >> temp_input;



    return 0;
}

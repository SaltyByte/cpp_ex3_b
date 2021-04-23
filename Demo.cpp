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
    NumberWithUnits a(1,"day");
    NumberWithUnits b(60*24,"min");

    boolalpha(cout);
    cout << (a > b) << endl;
    cout << (a < b) << endl;


    return 0;
}

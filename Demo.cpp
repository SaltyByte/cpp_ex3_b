#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    ofstream myfile;
    myfile.open ("myTestFile.txt");
    myfile << "1 km = 1000 m" << endl;
    myfile << "1 m = 100 cm" << endl;
    myfile << "1 kg = 1000 g" << endl;
    myfile << "1 ton = 1000 kg" << endl;
    myfile << "1 hour = 60 min" << endl;
    myfile << "1 min = 60 sec" << endl;
    myfile << "1 day = 24 hour" << endl;
    myfile << "1 month = 30 day" << endl;
    myfile << "1 year = 12 month" << endl;
    myfile.close();
    ifstream units_file{"myTestFile.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits day(1,"day");
    NumberWithUnits min(61*24,"min");


    if (day == min) {
        cout << "Good";
    }

  return 0;
}

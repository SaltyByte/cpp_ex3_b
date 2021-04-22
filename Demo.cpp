#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    ofstream File("units.txt");

    File << "1 km = 1000 m" << endl;
    File << "1 m = 100 cm" << endl;
    File << "1 cm = 10 mm" << endl;
    File << "1 kg = 1000 g" << endl;
    File << "1 ton = 1000 kg" << endl;
    File << "1 g = 1000 mg" << endl;
    File << "1 hour = 60 min" << endl;
    File << "1 min = 60 sec" << endl;
    File << "1 EUR = 4.5 ILS" << endl;
    File << "1 USD = 3.33 ILS ";
    // Close the file
    File.close();
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits ton_1(100,"sec");
    NumberWithUnits mg_1000000000(1,"hour");
    cout << ton_1 << endl;
    cout << NumberWithUnits(60*60,"sec") << endl;

  return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <float.h>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    ifstream units_file{"filename.txt"};
    ifstream units_file2{"filename2.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits::read_units(units_file2);

    NumberWithUnits temp_input(7, "r_ILS");



    NumberWithUnits a(7, "r_ILS");
    NumberWithUnits b(7, "r_ILS");
    NumberWithUnits c(7, "r_ILS");
    istringstream iss3{" -16 [r_m]   -7 [r_hour ]  8.8 [r_min ]"};
    iss3 >> a >> b >> c;



  return 0;
}

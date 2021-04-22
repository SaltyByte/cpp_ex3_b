#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    ifstream file("customFile.txt");
    NumberWithUnits::read_units(file);


    NumberWithUnits x(0.8325, "r_EUR");
    NumberWithUnits y(1, "r_USD");

    cout << x + y;
  return 0;
}

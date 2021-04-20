#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cmath>



using namespace std;
using namespace ariel;

double roundFourDigits(double val, double unitSize) {
    return round((val / unitSize) * 10000) / 10000;
}

TEST_CASE("Testing first row") {
    //This test tests only first row of the units file, works on every type of unit.
    ifstream units_file{"units.txt"};
    if (units_file.fail() || units_file.bad() || units_file.eof()) {
                FAIL("Error in opening file");
    }
    NumberWithUnits::read_units(units_file);

    string firstUnitName;
    string secondUnitName;
    double secondUnit;

    units_file.ignore(2) >> firstUnitName;
    units_file.ignore(2) >> secondUnit >> secondUnitName;
    units_file.clear();
    units_file.seekg(0);
    units_file.close();

    NumberWithUnits a{1, firstUnitName};
    NumberWithUnits b{4, firstUnitName};
    NumberWithUnits c{240, secondUnitName};

    // Test + and - with same unit object
    CHECK((a + b) == NumberWithUnits(5, firstUnitName));
    CHECK((b + a) == NumberWithUnits(5, firstUnitName));
    CHECK((a - b) == NumberWithUnits(-3, firstUnitName));
    CHECK((b - a) == NumberWithUnits(3, firstUnitName));

    // Test ++ and --- prefix and suffix
    CHECK((a++) == NumberWithUnits(2, firstUnitName));
    CHECK((b--) == NumberWithUnits(3, firstUnitName));
    CHECK((--a) == NumberWithUnits(1, firstUnitName));
    CHECK((++b) == NumberWithUnits(4, firstUnitName));

    // Test unary operation on "km"
    CHECK((+b) == NumberWithUnits(4, firstUnitName));
    CHECK((-b) == NumberWithUnits(-4, firstUnitName));
    CHECK((+a) == NumberWithUnits(1, firstUnitName));
    CHECK((-a) == NumberWithUnits(-1, firstUnitName));


    // Test + and - with different unit but same category
    CHECK((a + c) == NumberWithUnits(roundFourDigits(secondUnit + 240, secondUnit), firstUnitName));
    CHECK((b + c) == NumberWithUnits(roundFourDigits(secondUnit * 4 + 240, secondUnit), firstUnitName));
    CHECK((a - c) == NumberWithUnits(roundFourDigits(secondUnit - 240, secondUnit), firstUnitName));
    CHECK((b - c) == NumberWithUnits(roundFourDigits(secondUnit * 4 - 240, secondUnit), firstUnitName));

    CHECK((c + a) == NumberWithUnits(secondUnit + 240, secondUnitName));
    CHECK((c + b) == NumberWithUnits(secondUnit * 4 + 240, secondUnitName));
    CHECK((c - a) == NumberWithUnits(240 - secondUnit, secondUnitName));
    CHECK((c - b) == NumberWithUnits(240 - secondUnit * 4, secondUnitName));

    NumberWithUnits d{5, firstUnitName};
    NumberWithUnits e{3, firstUnitName};
    NumberWithUnits f{543, secondUnitName};


    CHECK((d += e) == NumberWithUnits(8, firstUnitName)); // d = 8
    CHECK((e += d) == NumberWithUnits(11, firstUnitName)); // e = 11
    CHECK((d -= e) == NumberWithUnits(-3, firstUnitName)); // d = -3
    CHECK((e -= d) == NumberWithUnits(14, firstUnitName)); // e = 14

    CHECK((d += f) == NumberWithUnits(roundFourDigits(secondUnit * (-3) + 543, secondUnit), firstUnitName)); // d = -2.457
    CHECK((e -= f) == NumberWithUnits(roundFourDigits(secondUnit * 14 - 543, secondUnit), firstUnitName)); // e = 13.457

    NumberWithUnits g{5, firstUnitName};
    NumberWithUnits h{3, firstUnitName};
    CHECK((f += g) == NumberWithUnits(secondUnit * 5 + 543, secondUnitName)); // f = 5,543
    CHECK((f -= h) == NumberWithUnits(5543 - secondUnit * 3, secondUnitName)); // f = 2543

    // Test unary operation on "m"
    CHECK((+c) == NumberWithUnits(240, secondUnitName));
    CHECK((-c) == NumberWithUnits(-240, secondUnitName));


    // Test ++ and -- prefix and suffix
    CHECK((c++) == NumberWithUnits(241,secondUnitName));
    CHECK((c--) == NumberWithUnits(240,secondUnitName));
    CHECK((--c) == NumberWithUnits(239,secondUnitName));
    CHECK((++c) == NumberWithUnits(240,secondUnitName));

    // Testing booleans operations
    CHECK((a > b) == false);
    CHECK((a < b) == true);
    CHECK((b > a) == true);
    CHECK((b < a) == false);

    CHECK((c > b) == false);
    CHECK((c < b) == true);
    CHECK((c > a) == false);
    CHECK((c < a) == true);

    CHECK((a == b) == false);
    CHECK((a >= b) == false);
    CHECK((a <= b) == true);
    CHECK((a != b) == true);

    CHECK((b == a) == false);
    CHECK((b >= a) == true);
    CHECK((b <= a) == false);
    CHECK((b != a) == true);

    CHECK((a == c) == false);
    CHECK((a >= c) == true);
    CHECK((a <= c) == false);
    CHECK((a != c) == true);

    CHECK((c == a) == false);
    CHECK((c >= a) == false);
    CHECK((c <= a) == true);
    CHECK((c != a) == true);

    NumberWithUnits i{2.5, firstUnitName};
    NumberWithUnits j{2.5 * secondUnit, secondUnitName};

    CHECK((i == j) == true);
    CHECK((i >= j) == true);
    CHECK((i <= j) == true);
    CHECK((i != j) == false);
}

TEST_CASE("Testing custom units") {
    ofstream new_file{"customFile.txt"};
    new_file << "1 km = 1000 m" << endl;
    new_file << "1 m = 100 cm" << endl;
    new_file << "1 USD = 3.33 ILS" << endl;
    new_file.close();

    ifstream units_file{"customFile.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{5, "km"};
    NumberWithUnits b{11, "km"};
    NumberWithUnits c{31, "m"};

    // Test + and - with same unit object
    CHECK((a + b) == NumberWithUnits(16, "km"));
    CHECK((b + a) == NumberWithUnits(16, "km"));
    CHECK((a - b) == NumberWithUnits(-6, "km"));
    CHECK((b - a) == NumberWithUnits(6, "km"));

    // Test ++ and --- prefix and suffix
    CHECK((a++) == NumberWithUnits(6, "km"));
    CHECK((b--) == NumberWithUnits(10, "km"));
    CHECK((--a) == NumberWithUnits(5, "km"));
    CHECK((++b) == NumberWithUnits(11, "km"));

    // Test unary operation on "km"
    CHECK((+b) == NumberWithUnits(11, "km"));
    CHECK((-b) == NumberWithUnits(-11, "km"));
    CHECK((+a) == NumberWithUnits(5, "km"));
    CHECK((-a) == NumberWithUnits(-5, "km"));

    // Test + and - with different unit but same category
    CHECK((a + c) == NumberWithUnits(5.031, "km"));
    CHECK((b + c) == NumberWithUnits(11.031, "km"));
    CHECK((a - c) == NumberWithUnits(4.969, "km"));
    CHECK((b - c) == NumberWithUnits(10.969, "km"));

    CHECK((c + a) == NumberWithUnits(5031, "m"));
    CHECK((c + b) == NumberWithUnits(11031, "m"));
    CHECK((c - a) == NumberWithUnits(-4969, "m"));
    CHECK((c - b) == NumberWithUnits(-10969, "m"));

    // Test unary operation on "m"
    CHECK((+c) == NumberWithUnits(31, "m"));
    CHECK((-c) == NumberWithUnits(-31, "m"));

    // Test ++ and -- prefix and suffix
    CHECK((c++) == NumberWithUnits(32, "m"));
    CHECK((c--) == NumberWithUnits(31, "m"));
    CHECK((--c) == NumberWithUnits(30, "m"));
    CHECK((++c) == NumberWithUnits(31, "m"));

    // Testing booleans operations
    CHECK((a > b) == false);
    CHECK((a < b) == true);
    CHECK((b > a) == true);
    CHECK((b < a) == false);

    CHECK((c > b) == false);
    CHECK((c < b) == true);
    CHECK((c > a) == false);
    CHECK((c < a) == true);

    CHECK((a == b) == false);
    CHECK((a >= b) == false);
    CHECK((a <= b) == true);
    CHECK((a != b) == true);

    CHECK((b == a) == false);
    CHECK((b >= a) == true);
    CHECK((b <= a) == false);
    CHECK((b != a) == true);

    CHECK((a == c) == false);
    CHECK((a >= c) == true);
    CHECK((a <= c) == false);
    CHECK((a != c) == true);

    CHECK((c == a) == false);
    CHECK((c >= a) == false);
    CHECK((c <= a) == true);
    CHECK((c != a) == true);

    NumberWithUnits f{2.5, "km"};
    NumberWithUnits g{2500, "m"};

    CHECK((f == g) == true);
    CHECK((f >= g) == true);
    CHECK((g <= f) == true);
    CHECK((f != g) == false);

}
TEST_CASE("Test throws"){
    ifstream units_file{"customFile.txt"};
    NumberWithUnits::read_units(units_file);
    if (units_file.fail() || units_file.bad() || units_file.eof()) {
                FAIL("Error in opening file");
    }
    //Bad case, using bad types.
    CHECK_THROWS(NumberWithUnits a(1,"Km"));
    CHECK_THROWS(NumberWithUnits b(1,"ils"));
    CHECK_THROWS(NumberWithUnits c(1,"Usd"));

    //None existent
    CHECK_THROWS(NumberWithUnits d(1,"a"));
    CHECK_THROWS(NumberWithUnits e(1,"us"));
    CHECK_THROWS(NumberWithUnits f(1,"kmm"));
    CHECK_THROWS(NumberWithUnits g(1,"k"));
    CHECK_THROWS(NumberWithUnits h(1,"K"));

    NumberWithUnits a{10,"km"};
    NumberWithUnits b{5,"ILS"};

    CHECK_THROWS(a + b);
    CHECK_THROWS(a - b);
    CHECK_THROWS(a += b);
    CHECK_THROWS(a -= b);
}


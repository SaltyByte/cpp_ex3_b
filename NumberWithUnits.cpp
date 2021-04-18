#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <tuple>


using namespace std;

namespace ariel {
    double getUnitSize(const string &unitLeft, const string &unitRight) {
        double retSize = 1;
        string unit = unitLeft;
        bool endOfMap = false;
        while (!endOfMap) {
            if (unitRight == unit) {
                return retSize;
            }
            if (unitsAvailable.find(unit) != unitsAvailable.end()) {
                retSize /= get<1>(unitsAvailable[unit]);
                unit = get<0>(unitsAvailable[unit]);
            } else {
                endOfMap = true;
            }
        }
        retSize = 1;
        endOfMap = false;
        unit = unitRight;
        while (!endOfMap) {
            if (unitLeft == unit) {
                return retSize;
            }
            if (unitsAvailable.find(unit) != unitsAvailable.end()) {
                retSize *= get<1>(unitsAvailable[unit]);
                unit = get<0>(unitsAvailable[unit]);
            } else {
                endOfMap = true;
            }
        }
        return -1;
    }


    void NumberWithUnits::read_units(ifstream &file) {
        if (file.fail() || file.eof() || file.bad()) {
            throw std::runtime_error("Error in opening file");
        }
        file.clear();
        file.seekg(0);
        // This while loop adds the units to the map
        while (!file.eof()) {
            string firstUnitName;
            string secondUnitName;
            double secondUnit = 0;

            file.ignore(2) >> firstUnitName;
            file.ignore(2) >> secondUnit >> secondUnitName;
            file.ignore(2);
            unitsAvailable[firstUnitName] = make_tuple(secondUnitName, secondUnit);

            /// ===adding to set here=====
            validUnits.insert(firstUnitName);
            validUnits.insert(secondUnitName);
            /// ===adding to set here=====

        }
        file.clear();
        file.seekg(0);
    }

    ostream &operator<<(std::ostream &os, const NumberWithUnits &unit) {
        os << unit.num_ << "[" << unit.str_ << ']';
        return os;
    }

    istream &operator>>(std::istream &is, NumberWithUnits &unit) {
        is >> unit.num_;
        is.ignore(2);
        is >> unit.str_;
        return is;
    }

    NumberWithUnits operator-(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        double sizeOfUnit = getUnitSize(unit1.str_, unit2.str_);
        if (sizeOfUnit == -1) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        return NumberWithUnits(unit1.num_ - unit2.num_ * sizeOfUnit, unit1.str_);
    }

    NumberWithUnits operator-(const NumberWithUnits &unit) {
        return NumberWithUnits(-unit.num_, unit.str_);
    }

    NumberWithUnits operator--(NumberWithUnits &unit) {
        unit.num_--;
        return unit;
    }

    NumberWithUnits operator--(NumberWithUnits &unit, int) {
        --unit.num_;
        return unit;
    }

    NumberWithUnits operator+(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        double sizeOfUnit = getUnitSize(unit1.str_, unit2.str_);
        if (sizeOfUnit == -1) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        return NumberWithUnits(unit1.num_ + unit2.num_ * sizeOfUnit, unit1.str_);
    }

    NumberWithUnits operator+(const NumberWithUnits &unit) {
        return NumberWithUnits(+unit.num_, unit.str_);
    }

    NumberWithUnits operator++(NumberWithUnits &unit) {
        unit.num_++;
        return unit;
    }

    NumberWithUnits operator++(NumberWithUnits &unit, int) {
        ++unit.num_;
        return unit;
    }

    NumberWithUnits operator*(const NumberWithUnits &unit, double val) {
        return NumberWithUnits(unit.num_ * val, unit.str_);
    }

    NumberWithUnits operator*(double val, const NumberWithUnits &unit) {
        return NumberWithUnits(val * unit.num_, unit.str_);
    }

    NumberWithUnits operator+=(NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return unit1 = unit1 + unit2;
    }

    NumberWithUnits operator-=(NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return unit1 = unit1 - unit2;
    }

    bool operator==(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        double sizeOfUnit = getUnitSize(unit1.str_, unit2.str_);
        if (sizeOfUnit == -1) {
            throw runtime_error("Wrong type of units, cant operate");
        }

        double temp = sizeOfUnit * unit2.num_;
        return temp == unit1.num_;

    }

    bool operator!=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return !(operator==(unit1, unit2));
    }

    bool operator<(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        double sizeOfUnit = getUnitSize(unit1.str_, unit2.str_);
        if (sizeOfUnit == -1) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit2.num_;
        return unit1.num_ < temp;

    }

    bool operator>(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        double sizeOfUnit = getUnitSize(unit1.str_, unit2.str_);
        if (sizeOfUnit == -1) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit2.num_;
        return unit1.num_ > temp;

    }

    bool operator<=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        double sizeOfUnit = getUnitSize(unit1.str_, unit2.str_);
        if (sizeOfUnit == -1) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit2.num_;
        return unit1.num_ <= temp;
    }

    bool operator>=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        double sizeOfUnit = getUnitSize(unit1.str_, unit2.str_);
        if (sizeOfUnit == -1) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit2.num_;
        return unit1.num_ >= temp;
    }
}
#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>


using namespace std;


namespace ariel {
    double const EPS = 0.00001;
    map <string, map<string, double>> NumberWithUnits::unitsAvailable;

    // Constructor
    NumberWithUnits::NumberWithUnits(double num, const std::string &str) {
        if (unitsAvailable.find(str) == unitsAvailable.end()) {
            throw runtime_error("Can not find the unit requested");
        }
        num_ = num;
        str_ = str;
    }
    // just checks if can operate on given units
    bool NumberWithUnits::checkUnits(const NumberWithUnits &unit1, const NumberWithUnits &unit2) { // map is double sided
        return unitsAvailable[unit1.str_].find(unit2.str_) == unitsAvailable[unit1.str_].end();    // so we can check only one side
    }

    // this function updates the units with new units every time inserting new units
    void NumberWithUnits::updateUnits(const string &unit1, const string &unit2) {
        for (auto &map : unitsAvailable[unit2]) { // iterate second map
            if (unitsAvailable[unit1].find(map.first) == unitsAvailable[unit1].end()) {
                double unitSize = unitsAvailable[unit1][unit2]; // take old ratio
                double newUnitSize = unitSize * map.second; // unit x second ratio, measures the new ratio.
                unitsAvailable[unit1][map.first] = newUnitSize; // update ratio
                unitsAvailable[map.first][unit1] = 1 / newUnitSize;
            }
        }
    }


    void NumberWithUnits::read_units(ifstream &file) {
        if (file.fail() || file.bad()) {
            throw runtime_error("Error in opening file");
        }
        file.clear();
        file.seekg(0);
        // This while loop adds the units to the map
        while (!file.eof()) {
            string firstUnitName;
            string secondUnitName;
            string skip;
            double secondUnit = 0;

            getline(file, skip, '1');
            file >> firstUnitName;
            if (firstUnitName.empty()) { // check if string is empty
                break;
            }
            getline(file, skip, '=');
            file >> secondUnit >> secondUnitName;

            // update map with units
            unitsAvailable[firstUnitName][secondUnitName] = secondUnit;
            unitsAvailable[secondUnitName][firstUnitName] = 1 / secondUnit;

            // update map with new units and ratios
            updateUnits(firstUnitName, secondUnitName);
            updateUnits(secondUnitName, firstUnitName);
        }
        file.clear();
        file.seekg(0);
    }

    ostream &operator<<(std::ostream &os, const NumberWithUnits &unit) {
        os << unit.num_ << '[' << unit.str_ << ']';
        return os;
    }

    istream &operator>>(std::istream &is, NumberWithUnits &unit) {
        string str;
        is >> unit.num_;
        getline(is, str, ']'); // take like till we get to ] and skip him
        str.erase(remove(str.begin(), str.end(), '['), str.end()); // erase all '['
        str.erase(remove(str.begin(), str.end(), ' '), str.end()); // erase all ' '
                                                                             // leaves up with only the unit
        if (NumberWithUnits::unitsAvailable.find(str) == NumberWithUnits::unitsAvailable.end()) {
            throw runtime_error("Can not find the unit requested");
        }
        unit.str_ = str;
        return is;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &unit) {
        if (checkUnits(*this, unit)) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double sizeOfUnit = unitsAvailable[unit.str_][this->str_];
        return NumberWithUnits(this->num_ - unit.num_ * sizeOfUnit, this->str_);
    }

    NumberWithUnits NumberWithUnits::operator-() {
        return NumberWithUnits(-this->num_, this->str_);
    }

    NumberWithUnits &NumberWithUnits::operator--() {
        this->num_--;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int) {
        NumberWithUnits ret = *this;
        this->num_--;
        return ret;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &unit) {
        if (checkUnits(*this, unit)) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double sizeOfUnit = unitsAvailable[unit.str_][this->str_];
        return NumberWithUnits(this->num_ + unit.num_ * sizeOfUnit, this->str_);
    }

    NumberWithUnits NumberWithUnits::operator+() {
        return NumberWithUnits(+this->num_, this->str_);
    }

    NumberWithUnits &NumberWithUnits::operator++() {
        this->num_++;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int) {
        NumberWithUnits ret = *this;
        this->num_++;
        return ret;
    }

    NumberWithUnits NumberWithUnits::operator*(double val) {
        return NumberWithUnits(this->num_ * val, this->str_);
    }

    NumberWithUnits operator*(double val, const NumberWithUnits &unit) {
        return NumberWithUnits(val * unit.num_, unit.str_);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &unit) {
        *this = *this + unit;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &unit) {
        *this = *this - unit;
        return *this;
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &unit) const {
        if (checkUnits(*this, unit)) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double sizeOfUnit = unitsAvailable[unit.str_][this->str_];
        double temp1 = sizeOfUnit * unit.num_;
        return abs(temp1 - this->num_) < EPS;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &unit) const {
        return !(operator==(unit));
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &unit) const {
        if (checkUnits(*this, unit)) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double sizeOfUnit = unitsAvailable[unit.str_][this->str_];
        double temp1 = sizeOfUnit * unit.num_;
        double temp2 = abs(this->num_ - temp1);
        if (temp2 < EPS) {
            return false;
        }
        return this->num_ < temp1;
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &unit) const {
        if (checkUnits(*this, unit)) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double sizeOfUnit = unitsAvailable[unit.str_][this->str_];
        double temp1 = sizeOfUnit * unit.num_;
        double temp2 = abs(this->num_ - temp1);
        if (temp2 < EPS) {
            return false;
        }
        return this->num_ > temp1;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &unit) const {
        if (checkUnits(*this, unit)) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double sizeOfUnit = unitsAvailable[unit.str_][this->str_];
        double temp1 = sizeOfUnit * unit.num_;
        double temp2 = abs(this->num_ - temp1);
        if (temp2 < EPS) {
            return true;
        }
        return this->num_ <= temp1;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &unit) const {
        if (checkUnits(*this, unit)) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double sizeOfUnit = unitsAvailable[unit.str_][this->str_];
        double temp1 = sizeOfUnit * unit.num_;
        double temp2 = abs(this->num_ - temp1);
        if (temp2 < EPS) {
            return true;
        }
        return this->num_ >= temp1;
    }
}
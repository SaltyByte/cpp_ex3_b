#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <tuple>


using namespace std;


namespace ariel {
    // todo fix <= >=
    // Constructor
    NumberWithUnits::NumberWithUnits(double num, const std::string &str) {
        if (validUnits.find(str) == validUnits.end()) {
            throw std::runtime_error("Can not find the unit requested");
        }
        num_ = num;
        str_ = str;
    }

    double sizeCalc(const string &unitLeft, const string &unitRight, int firstTime) {
        double retSize = 1;
        string unit = unitLeft;
        bool endOfMap = false;
        while (!endOfMap) {
            if (unitRight == unit) {
                return retSize;
            }
            if (unitsAvailable.find(unit) != unitsAvailable.end()) {
                if (firstTime) {
                    retSize /= get<1>(unitsAvailable[unit]);
                } else {
                    retSize *= get<1>(unitsAvailable[unit]);
                }
                unit = get<0>(unitsAvailable[unit]);
            } else {
                endOfMap = true;
            }
        }
        return -2;
    }

    double getUnitSize(const string &unitLeft, const string &unitRight) {
        double sizeOfUnit = sizeCalc(unitLeft, unitRight, true);
        if (sizeOfUnit == -2) {
            sizeOfUnit = sizeCalc(unitRight, unitLeft, false);
        }
        return sizeOfUnit;
    }


    void NumberWithUnits::read_units(ifstream &file) {
        if (file.fail() || file.bad()) {
            throw std::runtime_error("Error in opening file");
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
            if (firstUnitName.empty()) {
                break;
            }
            getline(file, skip, '=');
            file >> secondUnit >> secondUnitName;

            unitsAvailable[firstUnitName] = make_tuple(secondUnitName, secondUnit);

            validUnits.insert(firstUnitName);
            validUnits.insert(secondUnitName);

            for (auto const &val : unitsAvailable) {
                if (get<0>(unitsAvailable[firstUnitName]) == get<0>(unitsAvailable[val.first])
                    && val.first != firstUnitName) {
                    double leftUnitSize = get<1>(val.second) / secondUnit;
                    unitsAvailable[val.first] = make_tuple(firstUnitName, leftUnitSize);
                }
            }
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
        getline(is, str, '[');
        getline(is, str, ']');
        str.erase(std::remove(str.begin(), str.end(), ']'), str.end());
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

        if (validUnits.find(str) == validUnits.end()) {
            throw std::runtime_error("Can not find the unit requested");
        }
        unit.str_ = str;

        return is;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &unit) {
        double sizeOfUnit = getUnitSize(this->str_, unit.str_);
        if (sizeOfUnit == -2) {
            throw runtime_error("Wrong type of units, cant operate");
        }
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
        double sizeOfUnit = getUnitSize(this->str_, unit.str_);
        if (sizeOfUnit == -2) {
            throw runtime_error("Wrong type of units, cant operate");
        }
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
        double sizeOfUnit = getUnitSize(this->str_, unit.str_);
        if (sizeOfUnit == -2) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit.num_;
        return abs(temp - this->num_) < EPS;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &unit) const {
        return !(operator==(unit));
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &unit) const {
        double sizeOfUnit = getUnitSize(this->str_, unit.str_);
        if (sizeOfUnit == -2) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit.num_;
        return this->num_ < temp;

    }

    bool NumberWithUnits::operator>(const NumberWithUnits &unit) const {
        double sizeOfUnit = getUnitSize(this->str_, unit.str_);
        if (sizeOfUnit == -2) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit.num_;
        return this->num_ > temp;

    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &unit) const {
        double sizeOfUnit = getUnitSize(this->str_, unit.str_);
        if (sizeOfUnit == -2) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit.num_;
        return this->num_ <= temp;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &unit) const {
        double sizeOfUnit = getUnitSize(this->str_, unit.str_);
        if (sizeOfUnit == -2) {
            throw runtime_error("Wrong type of units, cant operate");
        }
        double temp = sizeOfUnit * unit.num_;
        return this->num_ >= temp;
    }
}
#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace ariel {
    // TODO fix all operators to work with all legit types.
    void NumberWithUnits::read_units(ifstream &file) {
        cout << "Hello World!" << endl;
    }

    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &unit) {
        os << unit.num_ << "[" << unit.str_ << ']';
        return os;
    }

    std::istream &operator>>(std::istream &is, NumberWithUnits &unit) {
        is >> unit.num_;
        return is;
    }

    NumberWithUnits operator-(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return NumberWithUnits(unit1.num_-unit2.num_, unit1.str_);
    }

    NumberWithUnits operator-(const NumberWithUnits &unit) {
        return NumberWithUnits(-unit.num_, unit.str_);
    }

    NumberWithUnits operator--(const NumberWithUnits &unit) {
        return NumberWithUnits(0, "");
    }

    NumberWithUnits operator--(const NumberWithUnits &unit, int) {
        return NumberWithUnits(0, "");
    }

    NumberWithUnits operator+(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return NumberWithUnits(unit1.num_ + unit2.num_, unit1.str_);
    }

    NumberWithUnits operator+(const NumberWithUnits &unit) {
        return NumberWithUnits(0, "");
    }

    NumberWithUnits operator++(const NumberWithUnits &unit) {
        return NumberWithUnits(0, "");
    }

    NumberWithUnits operator++(const NumberWithUnits &unit, int) {
        return NumberWithUnits(0, "");
    }

    NumberWithUnits operator*(const NumberWithUnits &unit, double val) {
        return NumberWithUnits(0, "");
    }

    NumberWithUnits operator*(double val, const NumberWithUnits &unit) {
        return NumberWithUnits(val * unit.num_, unit.str_);
    }

    NumberWithUnits operator+=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return NumberWithUnits(0, "");
    }

    NumberWithUnits operator-=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return NumberWithUnits(0, "");
    }

    bool operator==(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return unit1.num_ == unit2.num_ && unit1.str_ == unit2.str_;
    }

    bool operator!=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return !(operator==(unit1, unit2));
    }

    bool operator<(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return true;
    }

    bool operator>(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return true;
    }

    bool operator<=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return true;
    }

    bool operator>=(const NumberWithUnits &unit1, const NumberWithUnits &unit2) {
        return true;
    }

}
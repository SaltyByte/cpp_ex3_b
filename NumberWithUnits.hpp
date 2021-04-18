#ifndef EX_3_A_NUMBERWITHUNITS_HPP
#define EX_3_A_NUMBERWITHUNITS_HPP

#include <string>
#include <iostream>
#include <stdexcept>
#include <map>
#include <set>
#include <tuple>

namespace ariel {
    static std::map <std::string, std::tuple<std::string, double>> unitsAvailable;
    static std::set <std::string> validUnits;
    class NumberWithUnits {
    private:
        double num_;
        std::string str_;
    public:
        NumberWithUnits(double num, const std::string &str) {
            // todo check why set is empty!
//            if (validUnits.empty()) {
//                std::cout << "set is empty!" << std::endl;
//            }
//            if (!(validUnits.find(str) != validUnits.end())) {
//                throw std::runtime_error("Can not find the unit requested");
//            }
            num_ = num;
            str_ = str;
        }

        static void read_units(std::ifstream &file);

        //<<<<<<<================== ostream start ==================>>>>>>>
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &unit);
        //<<<<<<<================== ostream end   ==================>>>>>>>

        //<<<<<<<================== istream start ==================>>>>>>>
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &unit);
        //<<<<<<<================== istream end   ==================>>>>>>>

        //<<<<<<<================== -/-- start ==================>>>>>>>
        friend NumberWithUnits operator-(const NumberWithUnits &unit1, const NumberWithUnits &unit2);

        friend NumberWithUnits operator-(const NumberWithUnits &unit);

        friend NumberWithUnits operator--(NumberWithUnits &unit, int);

        friend NumberWithUnits operator--(NumberWithUnits &unit);
        //<<<<<<<================== -/-- end   ==================>>>>>>>

        //<<<<<<<================== +/++ start ==================>>>>>>>
        friend NumberWithUnits operator+(const NumberWithUnits &unit1, const NumberWithUnits &unit2);

        friend NumberWithUnits operator+(const NumberWithUnits &unit);

        friend NumberWithUnits operator++(NumberWithUnits &unit);

        friend NumberWithUnits operator++(NumberWithUnits &unit, int);
        //<<<<<<<================== +/++ end   ==================>>>>>>>

        //<<<<<<<================== * start ==================>>>>>>>
        friend NumberWithUnits operator*(const NumberWithUnits &unit, double val);

        friend NumberWithUnits operator*(double val, const NumberWithUnits &unit);
        //<<<<<<<================== * end   ==================>>>>>>>

        //<<<<<<<================== += start ==================>>>>>>>
        friend NumberWithUnits operator+=(NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== += end   ==================>>>>>>>

        //<<<<<<<================== -= start ==================>>>>>>>
        friend NumberWithUnits operator-=(NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== -= end   ==================>>>>>>>

        //<<<<<<<================== == start ==================>>>>>>>
        friend bool operator==(const NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== == end   ==================>>>>>>>

        //<<<<<<<================== != start ==================>>>>>>>
        friend bool operator!=(const NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== != end   ==================>>>>>>>

        //<<<<<<<================== < start ==================>>>>>>>
        friend bool operator<(const NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== < end   ==================>>>>>>>

        //<<<<<<<================== > start ==================>>>>>>>
        friend bool operator>(const NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== > end   ==================>>>>>>>

        //<<<<<<<================== <= start ==================>>>>>>>
        friend bool operator<=(const NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== <= end   ==================>>>>>>>

        //<<<<<<<================== >= start ==================>>>>>>>
        friend bool operator>=(const NumberWithUnits &unit1, const NumberWithUnits &unit2);
        //<<<<<<<================== >= end   ==================>>>>>>>
    };
}
#endif
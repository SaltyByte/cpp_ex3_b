#ifndef EX_3_A_NUMBERWITHUNITS_HPP
#define EX_3_A_NUMBERWITHUNITS_HPP

#include <string>
#include <iostream>
#include <stdexcept>
#include <map>
#include <set>
#include <tuple>

namespace ariel {
    static std::set <std::string> validUnits;
    static std::map <std::string, std::tuple<std::string, double>> unitsAvailable;
    class NumberWithUnits {
    private:
        double num_;
        std::string str_;
    public:
        NumberWithUnits(double num, const std::string &str);

        static void read_units(std::ifstream &file);

        //<<<<<<<================== ostream start ==================>>>>>>>
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &unit);
        //<<<<<<<================== ostream end   ==================>>>>>>>

        //<<<<<<<================== istream start ==================>>>>>>>
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &unit);
        //<<<<<<<================== istream end   ==================>>>>>>>

        //<<<<<<<================== -/-- start ==================>>>>>>>
        NumberWithUnits operator-(const NumberWithUnits &unit);

        NumberWithUnits operator-();

        NumberWithUnits operator--(int);

        NumberWithUnits &operator--();
        //<<<<<<<================== -/-- end   ==================>>>>>>>

        //<<<<<<<================== +/++ start ==================>>>>>>>
        NumberWithUnits operator+(const NumberWithUnits &unit);

        NumberWithUnits operator+();

        NumberWithUnits &operator++();

        NumberWithUnits operator++(int);
        //<<<<<<<================== +/++ end   ==================>>>>>>>

        //<<<<<<<================== * start ==================>>>>>>>
        NumberWithUnits operator*(double val);

        friend NumberWithUnits operator*(double val, const NumberWithUnits &unit);
        //<<<<<<<================== * end   ==================>>>>>>>

        //<<<<<<<================== += start ==================>>>>>>>
        NumberWithUnits &operator+=(const NumberWithUnits &unit);
        //<<<<<<<================== += end   ==================>>>>>>>

        //<<<<<<<================== -= start ==================>>>>>>>
        NumberWithUnits &operator-=(const NumberWithUnits &unit);
        //<<<<<<<================== -= end   ==================>>>>>>>

        //<<<<<<<================== == start ==================>>>>>>>
        bool operator==(const NumberWithUnits &unit) const;
        //<<<<<<<================== == end   ==================>>>>>>>

        //<<<<<<<================== != start ==================>>>>>>>
        bool operator!=(const NumberWithUnits &unit) const;
        //<<<<<<<================== != end   ==================>>>>>>>

        //<<<<<<<================== < start ==================>>>>>>>
        bool operator<(const NumberWithUnits &unit) const;
        //<<<<<<<================== < end   ==================>>>>>>>

        //<<<<<<<================== > start ==================>>>>>>>
        bool operator>(const NumberWithUnits &unit) const;
        //<<<<<<<================== > end   ==================>>>>>>>

        //<<<<<<<================== <= start ==================>>>>>>>
        bool operator<=(const NumberWithUnits &unit) const;
        //<<<<<<<================== <= end   ==================>>>>>>>

        //<<<<<<<================== >= start ==================>>>>>>>
        bool operator>=(const NumberWithUnits &unit) const;
        //<<<<<<<================== >= end   ==================>>>>>>>
    };
}
#endif
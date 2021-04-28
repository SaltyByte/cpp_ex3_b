#ifndef EX_3_A_NUMBERWITHUNITS_HPP
#define EX_3_A_NUMBERWITHUNITS_HPP

#include <string>
#include <iostream>
#include <stdexcept>
#include <map>

namespace ariel {
    class NumberWithUnits {
    private:
        // static map
        static std::map <std::string, std::map<std::string, double>> unitsAvailable;
        // static functions
        static void updateUnits(const std::string&, const std::string&);
        static bool checkUnits(const NumberWithUnits&, const NumberWithUnits&);
        // private variables
        double num_;
        std::string str_;

    public:
        // constructor
        NumberWithUnits(double num, const std::string &str);
        // units read
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
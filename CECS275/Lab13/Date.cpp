#include "Date.h"
#include <iostream>
#include <iomanip>
#include <string>

class Date{
    private:
        int month;
        int day;
        int year;
    
    public:
        int getMonth(void) const;               // returns month (ACCESSOR)
        int getDay(void) const;                 // returns date  (ACCESSOR)
        int getYear(void) const;                // returns year  (ACCESSOR)

        void displayDateNums(void) const;       // format: 08/25/2025
        void displayMonthDayYear(void) const;   // format: August 25, 2025
        void displayDayMonthYear(void) const;   // format: 25 August 2025

        bool isLeapYear(void) const;            
        int dateDifference(void) const;         // find difference between two dates

        void incDateOne();                  // Increase a date by one. (MUTATOR)
        void decDateOne();                  // Decrease a date by one. (MUTATOR)
        int dateCompare();                  // Compare two dates (return 1 if date1 > date2, 0 if date1 == date2, and -1 if date1 < date2)
};

/*
 * Returns month
*/
int Date::getMonth(void) const{
    return month;
}

/*
 * Returns Day
*/
int Date::getDay(void) const{
    return day;
}

/*
 * Returns year
*/
int Date::getYear(void) const{
    return year;
}

void Date::displayDateNums(void) const{
    std::cout << std::setw(2) << std::setfill('0') << month << '/'
              << std::setw(2) << std::setfill('0') << day   << '/'
              << year << std::endl;
}

void Date::displayMonthDayYear(void) const{
    std::string monthInYear[] = {
                       "January", "February", "March", 
                       "April", "May", "June", "July", 
                       "August", "September", "October", 
                       "November", "December"
                    };
    std::cout << monthInYear[getMonth() - 1] 
              << ' ' << day << ", " << year << std::endl;
}

void Date::displayDayMonthYear(void) const{
    std::string monthInYear[] = {
                       "January", "February", "March", 
                       "April", "May", "June", "July", 
                       "August", "September", "October", 
                       "November", "December"
                    };
    std::cout << day << ' ' << monthInYear[month] << ' ' << year << std::endl;
}

bool Date::isLeapYear(void) const{
    // divisible by 4
    // not divisible by 100 UNLESS also divisible by 400
    if( (year % 4 == 0) ){
        if(year % 400 == 0)
            return true;
        else if(year % 100 == 0)
            return false;
    }
    return false;
}

int Date::dateDifference(void) const{
    
}
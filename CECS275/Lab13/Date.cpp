#include "Date.h"
#include <iostream>
#include <iomanip>
#include <string>

// setting it to Epoch time
Date::Date(void){
    month = 1;
    year = 1970;
    day = 1;
}

// OVERLAODED CONSTRUCTOR
Date::Date(int month, int day, int year){
    // Ensure valid month
    if(month <= 12 && month >= 1)
        this-> month = month;
    else
        this -> month = 0;

    // Ensure valid day
    if(month == 2){     // Check Feb 
        if(day <= 28 && !isLeapYear())
            this-> day = day;
        else if(isLeapYear() && day <= 29)
            this -> day = day;
        else
            this -> day = 1;
    }else if(month == 1 || month == 3 || month == 5 || month == 7       // 31 day months
                        || month == 8 || month == 10 || month == 12){
        if(day <= 31)
            this -> day = day;
        else
            this -> day = 1;
    }else{              // 30 day months
        if(day <= 30)
            this -> day = day;
        else
            this -> day = 1;
    }

    // All years are valid
    this-> year = year;
}

////////////////////////// GETTERS/SETTERS //////////////////////////

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

void Date::setYear(int year){
    this -> year = year;
}

void Date::setMonth(int month){
    this -> month = month;
}

void Date::setDay(int day){
    this -> day = day;
}

////////////////////////////////////////////////////////////////////////

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

void Date::incDateOne(void){

}

void Date::decDateOne(void){

}

int Date::dateCompare(void){

}
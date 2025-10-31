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
    setMonth(month);
    setDay(day);
    setYear(year);
}

// OVERLOADED CONSTRUCTOR: COPY
// Date::Date(const Date &classToCopy){
//     setMonth(classToCopy.getMonth());
//     setDay(classToCopy.getDay());
//     setYear(classToCopy.getYear());
// }

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
    // Ensure years are valid
    if(year > 0)
        this -> year = year;
    else{
        this -> year = 1970;
        std::cout << year << " is an invalid year! Setting year to 1970." << std::endl;
    }
}

void Date::setMonth(int month){
    // Ensure valid month
    if(month <= 12 && month >= 1)
        this-> month = month;
    else{
        this -> month = 1;
        std::cout << month << " is an invalid month! Setting month to 1." << std::endl;
    }
}

void Date::setDay(int day){
     // Ensure valid day
    int month = getMonth();
    if(month == 2){     // Check Feb 
        if(day <= 28 && !isLeapYear())
            this-> day = day;
        else if(isLeapYear() && day <= 29)
            this -> day = day;
        else{
            this -> day = 1;
            std::cout << day << " is an invalid day! Setting day to 1." << std::endl;
        }
    }else if(month == 1 || month == 3 || month == 5 || month == 7       // 31 day months
                        || month == 8 || month == 10 || month == 12){
        if(day <= 31)
            this -> day = day;
        else{
            this -> day = 1;
            std::cout << day << " is an invalid day! Setting day to 1." << std::endl;
        }
    }else{              // 30 day months
        if(day <= 30)
            this -> day = day;
        else{
            this -> day = 1;
            std::cout << day << " is an invalid day! Setting day to 1." << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
              << ' ' << getDay() << ", " << getYear() << std::endl;
}

void Date::displayDayMonthYear(void) const{
    std::string monthInYear[] = {
                       "January", "February", "March", 
                       "April", "May", "June", "July", 
                       "August", "September", "October", 
                       "November", "December"
                    };
    std::cout << getDay() << ' ' << monthInYear[getMonth() - 1] << ' ' << getYear() << std::endl;
}

bool Date::isLeapYear(void) const{
    // divisible by 4
    // not divisible by 100 UNLESS also divisible by 400
    if( (getYear() % 4 == 0) ){
        if(getYear() % 400 == 0)
            return true;
        else if(getYear() % 100 == 0) // bc it's already not divisible by 400
            return false;
        return true;
    }
    return false;
}

int Date::dateDifference(Date subtractor) const{ // I am built evil
    // solution to compare: SUM UP ALL DAYS IN THAT DATE AND THEN COMPARE PROPERLY
   unsigned long long int differnceDay = 0;
   long long int baseDay = this -> day;
   long long int subDay = subtractor.getDay();

    for (long long int i = 0; i < year ; i++){ // determine the amt years and 
        if( (i% 4 == 0) ){
            if( i % 400 == 0)
                baseDay += 366;
            else if(i % 100 == 0) // bc it's already not divisible by 400
                baseDay += 365;
            else baseDay += 366;
        }
        else baseDay += 365;
        //std::cout << "BASEdAY YR"  << baseDay << std::endl;
    }

    // SUBTRACTOR
    for (long long int i = 0; i < subtractor.getYear(); i++){ // determine the amt years and 
        if( (i% 4 == 0) ){
            if( i % 400 == 0)
                subDay += 366;
            else if(i % 100 == 0) // bc it's already not divisible by 400
                subDay += 365;
            else subDay += 366;
        }
        else subDay += 365;
        //std::cout << "SUBdAY YR" << subDay << std::endl;
    }
    //std::cout << subDay << std::endl;

    //MONTH 2 DAYS
    //BASE DAY
    for (int i = 1; i <= month-1; i++){
        if(i == 2){     // Check Feb 
            if(!isLeapYear())
                baseDay += 28;
            else 
                baseDay += 29;
        }else if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) //31 days
            baseDay += 31;
        else              // 30 day months
            baseDay += 30;
        //std::cout <<"baseDAY IN MOTH LOOP: " << baseDay << std::endl;
    }
    //SUBTRACTOR
    for (int i = 1; i <= subtractor.getMonth()-1; i++){
        if(i == 2){     // Check Feb 
            if(!subtractor.isLeapYear())
                subDay += 28;
            else 
                subDay += 29;
        }else if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) //31 days
            subDay += 31;
        else{              // 30 day months
            subDay += 30;
        }
        //std::cout <<"subDAY IN MOTH LOOP: " << subDay << std::endl;
    }

    if (baseDay - subDay >= 0)
        return  baseDay - subDay;
    else
        return  subDay - baseDay;


}

void Date::incDateOne(void){
    //determine max days based on leap year, and month
    int monthLastDay = 0;
    if(month == 2){     // Check Feb 
        if(day <= 28 && !isLeapYear())
            monthLastDay = 28;
        
        else if(isLeapYear() && day <= 29)
            monthLastDay = 29;

    }else if(month == 1 || month == 3 || month == 5 || month == 7       // 31 day months
                        || month == 8 || month == 10 || month == 12){
        if(day <= 31)
            monthLastDay = 31;

    }else{              // 30 day months
        if(day <= 30)
            monthLastDay = 30;
    }

    //the actual mutation of year, month, day
    if (day < monthLastDay){// determines if the current day is not the Last Day of the month 
        this -> day++;

    } else{ //it is the current day is the last day of the month
        if(month < 12){ //determines if the current month is not the last month in a year
            this -> month++;
            this -> day++;

        } else{ // current month is the last month in a year
            this -> year++;
            this -> month = 1;
            this -> day = 1;

        }
    }
}

void Date::decDateOne(void){
    //
    int monthLastDay = 0;
    if(month == 2){     // Check Feb 
        if(day <= 28 && !isLeapYear())
            monthLastDay = 28;
        
        else if(isLeapYear() && day <= 29)
            monthLastDay = 29;

    }else if(month == 1 || month == 3 || month == 5 || month == 7       // 31 day months
                        || month == 8 || month == 10 || month == 12){
        if(day <= 31)
            monthLastDay = 31;

    }else{              // 30 day months
        if(day <= 30)
            monthLastDay = 30;
    }


    if (day > 1){// determines if the current day is not the First Day of the month 
        this -> day--;

    } else{ //it is the current day is the first day of the month
        if(month > 1){ //determines if the current month is not the first month in a year
            this -> month--;
            this -> day = monthLastDay;

        } else{ // current month is the first month in a year
            this -> year--;
            this -> month = 12;
            this -> day = monthLastDay;

        }
    }
}

int Date::dateCompare(Date first) const{
    // check if a year is less or more
    if(this -> getYear() > first.getYear())
        return 1;
    else if(this -> getYear() < first.getYear())
        return -1;
    // assume it will either fall into those;;  if not, then it is equal to.

    // check if a month is less or more
    if(this -> getMonth() > first.getMonth())
        return 1;
    else if(this -> getMonth() < first.getMonth())
        return -1;
    
    // then assume that year is equal and month is equal
    if(this -> getDay() > first.getDay())
        return 1;
    else if(this -> getDay() < first.getDay())
        return -1;

    // they're all equal to each other
    return 0;
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////// OVERLOADING OPERATORS /////////////////////////////////////////////////////////

Date Date::operator=(const Date &right){
    if(this == &right)
        return *this;

    // copy fields from right using setters
    setMonth(right.getMonth());
    setDay(right.getDay());
    setYear(right.getYear());

    return *this;
}

// Overload operator - to find the number of dates between two dates.
int Date::operator-(const Date &rightDate) const {
    return this->dateDifference(rightDate);
}

// Overload prefix ++ to increase a date by one.
void Date::operator++(){
    incDateOne();
}

// Overload postfix ++ to increase a date by one.
void Date::operator++(int x){
    incDateOne();
}

// Overload prefix -- to decrease date by one
void Date::operator--(){
    decDateOne();
}

// Overload postfix ++ to decrease date by one
void Date::operator--(int x){
    decDateOne();
}

// Compare left and right side; if left is less than:
bool Date::operator<(const Date &right) const{
    // int res = this -> dateCompare(right);
    if( (this -> dateCompare(right)) == -1)
        return true;
    return false;
}

// Compare left and right side; if left is greater than:
bool Date::operator>(const Date &right) const{
    // int res = this -> dateCompare(right);
    if( (this -> dateCompare(right)) == 1)
        return true;
    return false;
}

// Compare left and right side; if left is same as right:
bool Date::operator==(const Date &right) const{
    if( this -> dateCompare(right) == 0)
        return true;
    return false;
}

int Date::operator-(Date &right){

}

int Date::operator+(Date &right){
    
}
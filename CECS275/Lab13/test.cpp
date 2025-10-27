#include "Date.h"
#include <iostream>
using namespace std;

int main(void){
    Date May29_1928(05,29,1928);
    Date March18_2075(03, 18, 2075);
    Date failedDate(0, 100, -23);

    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "////////////////////////////////// May 29, 1928  ////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;

    cout << "May 29, 1928 day: " << May29_1928.getDay() << endl;
    cout << "May 29, 1928 month: " << May29_1928.getMonth() << endl;
    cout << "May 29, 1928 year: " << May29_1928.getYear() << endl;
    
    cout << "-------------------------------------------------------------------------------------------------" << endl;
    
    cout << "May 29 1928 MM/DD/YYYY Format: ";
    May29_1928.displayDateNums();

    cout << "-------------------------------------------------------------------------------------------------" << endl;
    
    cout << "\nMay 29 1928 Month Day  Year Format: ";
    May29_1928.displayMonthDayYear();

    cout << "-------------------------------------------------------------------------------------------------" << endl;
    
    cout << "\nMay 29 1928 Day Month Year Format: ";
    May29_1928.displayDayMonthYear();
    cout << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl;
    
    cout << "Check if May 29, 1928 leap year: " << May29_1928.isLeapYear() << endl;

    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////// FAILED DATE /////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;

    cout << "100 day: " << failedDate.getDay() << endl;
    cout << "0 month: " << failedDate.getMonth() << endl;
    cout << "-23 year: " << failedDate.getYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl;

    cout << "Changing the date with inappropriate numbers to appropriate." << endl;

    failedDate.setDay(10);
    failedDate.setMonth(10);
    failedDate.setYear(2010);

    cout << "Day: " << failedDate.getDay() << endl;
    cout << "Month: " << failedDate.getMonth() << endl;
    cout << "Year: " << failedDate.getYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl;

    cout << "Check if leap year: " << failedDate.isLeapYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl;

    cout << "Increasing date by one." << endl;
    failedDate.incDateOne();
    cout << "Day: " << failedDate.getDay() << endl;
    cout << "Month: " << failedDate.getMonth() << endl;
    cout << "Year: " << failedDate.getYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl;

    cout << "Decrease date by one." << endl;
    failedDate.decDateOne();
    cout << "Day: " << failedDate.getDay() << endl;
    cout << "Month: " << failedDate.getMonth() << endl;
    cout << "Year: " << failedDate.getYear() << endl;

    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "//////////////////////////////////// DATE DIFF //////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;

    cout << "Date Difference: " << failedDate.dateDifference(May29_1928) << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl;

    cout << "Date Comparison: " << failedDate.dateCompare(May29_1928) << endl;

}
#include "Date.h"
#include <iostream>
#include <ostream>
using namespace std;

int main(void){
    Date May29_1928(05,29,1928);
    Date March18_2075(03, 18, 2075);


    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "////////////////////////////////// May 29, 1928  ////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl << endl;

    cout << "May 29, 1928 day: " << May29_1928.getDay() << endl;
    cout << "May 29, 1928 month: " << May29_1928.getMonth() << endl;
    cout << "May 29, 1928 year: " << May29_1928.getYear() << endl;
    
    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
    
    cout << "May 29 1928 MM/DD/YYYY Format: ";
    May29_1928.displayDateNums();

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
    
    cout << "\nMay 29 1928 Month Day  Year Format: ";
    May29_1928.displayMonthDayYear();

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
    
    cout << "\nMay 29 1928 Day Month Year Format: ";
    May29_1928.displayDayMonthYear();
    cout << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
    
    cout << "Check if May 29, 1928 leap year: " << May29_1928.isLeapYear() << endl;

    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////// FAILED DATE /////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl << endl;
    Date failedDate(0, 100, -23);

    cout << "100 day: " << failedDate.getDay() << endl;
    cout << "0 month: " << failedDate.getMonth() << endl;
    cout << "-23 year: " << failedDate.getYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "Changing the date with inappropriate numbers to appropriate." << endl;

    failedDate.setDay(10);
    failedDate.setMonth(10);
    failedDate.setYear(2010);

    cout << "Day: " << failedDate.getDay() << endl;
    cout << "Month: " << failedDate.getMonth() << endl;
    cout << "Year: " << failedDate.getYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "Check if leap year: " << failedDate.isLeapYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "Increasing date by one." << endl;
    failedDate.incDateOne();
    cout << "Day: " << failedDate.getDay() << endl;
    cout << "Month: " << failedDate.getMonth() << endl;
    cout << "Year: " << failedDate.getYear() << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "Decrease date by one." << endl;
    failedDate.decDateOne();
    cout << "Day: " << failedDate.getDay() << endl;
    cout << "Month: " << failedDate.getMonth() << endl;
    cout << "Year: " << failedDate.getYear() << endl;

    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "//////////////////////////////////// DATE DIFF //////////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl << endl;

    cout << "Date Difference in days: " << failedDate.dateDifference(May29_1928) << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    if (failedDate.dateCompare(May29_1928) == 1) 
        cout << "Date Comparison: The First Date is Larger." << endl;
    else if(failedDate.dateCompare(May29_1928) == -1)
        cout << "Date Comparison: The second Date is Larger." << endl;
    else
        cout << "Date Comparison: The Dates are the same." << endl;


    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << "////////////////////////////////// Date Operators ///////////////////////////////////////////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl << endl;

    cout << "Print Checks: " << May29_1928 << endl;

    cout << "Regular Print: " << May29_1928.displayMonthDayYear() << endl; 
 
    cout << "Overloaded Operator Print: " << May29_1928 << endl;
    
    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "Increments and Decrements:" << endl;

    cout << May29_1928++ << endl;

    cout << May29_1928--;

    cout << ++May29_1928;
    
    cout << --May29_1928;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "Greater than Checks: " << endl;

    if( May29_1928 > March18_2075)
        cout << May29_1928 << " is greater than " << March18_2075 << endl;  
    else
        cout << May29_1928 << " is not greater than " << March18_2075 << endl;  

    if( March18_2075 > May29_1928)
        cout << March18_2075 << " is greater than " << May29_1928 << endl;  
    else
        cout << March18_2075 << " is not greater than " << May29_1928<< endl;  

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
    
    cout << "Less Than checks: " << endl;

    if( March18_2075 < May29_1928)
        cout << March18_2075 << " is less than " << May29_1928 << endl;  
    else
        cout << March18_2075 << " is not less than " << May29_1928<< endl;  

    if( May29_1928 < March18_2075)
        cout << May29_1928 << " is less than " << March18_2075 << endl;  
    else
        cout << May29_1928 << " is not less than " << March18_2075 << endl;  

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
    
    cout << "Equal to Checks: "<< endl;

    if( May29_1928 == March18_2075)
        cout << May29_1928 << " is equal than " << March18_2075 << endl;  
    else
        cout << May29_1928 << " is not equal than " << March18_2075 << endl;  

    if( May29_1928 == May29_1928)
        cout << May29_1928 << " is equal than " << May29_1928 << endl;  
    else
        cout << May29_1928 << " is not equal than " << May29_1928 << endl;  
    
    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
    Date copyingDate(06, 07, 2023);
    Date copiedDate(void);

    cout << "Copy and Difference: "<< endl;

    cout << "Copied date: " << copiedDate << endl;
    
    cout << "Copying date original: " << copyingDate << endl;

    cout << "Date Difference before: " << copyingDate - copyingDate << endl;

    cout << "Copied date after: " << copyingDate = copiedDate << endl;

    cout << "Date Difference after: " << copyingDate-copyingDate << endl;

    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;

    Date October31_2025(10, 31, 2025); //a halloween i was robbed >:(
    copiedDate = October31_2025;
    cout << "Date before Advance and Recede: " << October31_2025 << endl;

    cout << "Date Advance by 80085: " << October31_2025 + 80085;

    cout << "Date Difference after Advance: " << October31_2025-copiedDate << endl;

    cout << "Date Recede by 80085: " << October31_2025 - 80085;

    cout << "Date Difference after Recede: " << October31_2025-copiedDate << endl;


    cout << "-------------------------------------------------------------------------------------------------" << endl << endl;
}
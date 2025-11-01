#ifndef DATE_H
#define DATE_H
#include <ostream>
class Date{
    private:
        int month;
        int day;
        int year;
    
    public:
        Date(void);                                      // Constructor (default)
        explicit Date(int month, int day, int year);     // Overloaded Constructor
        //Date(const Date &classToCopy);                   // Overloaded Constructor: Copy ????

        int getMonth(void) const;               // returns month (ACCESSOR)
        int getDay(void) const;                 // returns date  (ACCESSOR)
        int getYear(void) const;                // returns year  (ACCESSOR)

        void setMonth(int month);               // Change month val
        void setDay(int day);                   // Change day val
        void setYear(int year);                 // change year val
        
        std::string displayDateNums(void) const;       // format: 08/25/2025
        std::string displayMonthDayYear(void) const;   // format: August 25, 2025
        std::string displayDayMonthYear(void) const;   // format: 25 August 2025

        bool isLeapYear(void) const;            
        int dateDifference(Date) const;         // find difference between two dates

        void incDateOne(void);                  // Increase a date by one. (MUTATOR)
        void decDateOne(void);                  // Decrease a date by one. (MUTATOR)
        int dateCompare(Date) const;            // Compare two dates (return 1 if date1 > date2, 0 if date1 == date2, and -1 if date1 < date2)

        Date operator=(const Date &right); // Is this the copy constructor?

        int operator-(const Date &rightSide) const;   // Overload operator - to find the number of dates between two dates.
        
        void operator++();                      // Overload prefix ++ to increase a date by one.
        void operator++(int);                   // Overload postfix ++ to increase a date by one.

        void operator--();                      // Overload prefix -- to decrease a date by one.
        void operator--(int);                   // Overload postfix -- to decrease a date by one.

        bool operator<(const Date &right) const;    // Compare left and right side; if left is less than:
        bool operator>(const Date &right) const;    // Compare left and right side; if left is greater than:
        bool operator==(const Date &right) const;   // Compare left and right side; if left is same as right:

        int operator+(Date &right);       // Overload + to calculate the date in the future after advancing a number of days from a current date
        int operator-(Date &right);       // Overload - to calculate the date in the past after receding a number of days from a current date
        
        std::ostream operator<<(const Date &right);
};

#endif
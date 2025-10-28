#ifndef DATE_H
#define DATE_H
class Date{
    private:
        int month;
        int day;
        int year;
    
    public:
        Date(void);                             // Constructor (default)
        explicit Date(int month, int day, int year);     // Overloaded Constructor

        int getMonth(void) const;               // returns month (ACCESSOR)
        int getDay(void) const;                 // returns date  (ACCESSOR)
        int getYear(void) const;                // returns year  (ACCESSOR)

        void setMonth(int month);               // Change month val
        void setDay(int day);                   // Change day val
        void setYear(int year);                 // change year val
        
        void displayDateNums(void) const;       // format: 08/25/2025
        void displayMonthDayYear(void) const;   // format: August 25, 2025
        void displayDayMonthYear(void) const;   // format: 25 August 2025

        bool isLeapYear(void) const;            
        int dateDifference(Date) const;         // find difference between two dates

        void incDateOne(void);                  // Increase a date by one. (MUTATOR)
        void decDateOne(void);                  // Decrease a date by one. (MUTATOR)
        int dateCompare(Date) const;                  // Compare two dates (return 1 if date1 > date2, 0 if date1 == date2, and -1 if date1 < date2)
};

#endif
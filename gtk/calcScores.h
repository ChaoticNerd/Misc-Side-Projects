#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class calcScore{
    private:
        // Grade weights
        const double gradeWeights[5] = {0.15, 0.15, .40, 0.10, 0.20};

        // Converts fractional value to percentage
        const int TO_PERCENT = 100;
        const double GradeA = 0.90,
                     GradeB = 0.80,
                     GradeC = 0.70,
                     GradeD = 0.60;

        const int AMOUNT_OF_CATEGORIES[5] = {1, 1, 1, 1, 1};

        // variables used to manipulate the class
        fstream inputFile;
        string fileName, dropped;
        vector<double> calculatedPercentages, averageScores;
        vector<vector<double>> calculatedClassPercentages;
        vector<vector<vector<double>>> allGrades;

        // default set to 100
        // TODO: requires setter to change threshold
        double threshold;

        //   default 0, default 40,       default 0s,                 default 10, 5, etc.
        // TODO: all these require setters
        int studentID, classSize, totalAssignmentsDropped[5], totalAssignments[5];

        // default false
        // TODO: requires setter for filestream upload
        bool isFileUploaded;

        // functions called within the class only
        void bubbleSort(vector<vector<double>> &calculatedClassPercentages);

        void getTotalPercentage(vector<vector<double>> &calculatedClassPercentages);

        void dropLowestScore(vector<vector<vector<double>>> (&allGrades), int typeOfAssignment);

        void getPoints(fstream& file, vector<vector<vector<double>>> &allGrades);
        void getTotalAssignments(fstream& file, int (&totalAssignmentsArray)[5]);

        void populateGradeVector(int (&totalAssignmentAmount)[5], vector<vector<vector<double>>> &allGrades, int amountOfStudents);
        void populateStudentVector(int (&totalAssignmentAmount)[5], vector<vector<double>> &allGrades, int amountOfStudents);

        std::string getLetterGrade(vector<double> &calculatedPercentages);
        std::string getLetterGradeSorted(vector<double> &calculatedPercentages);

        void calculatePercentage(double grade, double total, double gradeWeight, vector<double> &calculatedPercentages);
        void calculateClassPercentage(vector<vector<vector<double>>> grade, vector<double> total, double gradeWeight, vector<vector<double>> &calculatedPercentages, int assignmentType);
        
        void getAverageOfCategory(double pointsEarned, int amountOfAssignments, vector<double> &averageOfSingleCategory);
        void getAverageOfCategoryOfClass(vector<vector<double>> calculatedPercentages, int assignmentType, vector<double> &averageOfSingleCategory);

        void getIndividualStudentPointsTotal(vector<vector<vector<double>>> &allGrades, int studentNumber, int (&totalAssignments)[5], vector<double> &totalEarnedPoints);
        void getTotalScoresOfOneCategory(vector<vector<vector<double>>> &allGrades, int assignmentType, vector<vector<vector<double>>> &totalCategoryPoints);

        
    public:
        // TODO: CONSTRUCTOR
        calcScore(); // default constructor

        calcScore(fstream inFile, string fileName, vector<double> calcPerc, vector<double> avgScore, vector<vector<double>> calcClassPerc, vector<vector<vector<double>>> allGrades, int studentID,
                  int classSize);


        void generateReportClass(int classSize, int sortSelect, int isGradesDropped);

        void generateReportOneStudent(int isGradesDropped, int studentNumber);
        int checkFile(void);
        void printMenu(void);
        void fileImport(fstream &file);

        // TODO: DESTRUCTOR
        // vector dumptruck is constructor destructor
        ~calcScore();
        void vector_dumptruck(void);

        // print results
        void printResults(void);

        // threshscore
        void threshScore( double threshold, int isHigh);

        // print class sorted results
        void printClassSortedResults(void);
        void printClassResults(void);

        // FOR DEBUGGING
        void testPrintVector(vector<vector<double>> &allGrades);
};






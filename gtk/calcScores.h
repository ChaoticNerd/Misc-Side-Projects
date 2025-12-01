#ifndef CALCSCORES_H
#define CALCSCORES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class calcScore {
   private:

      // Grade weights (A, B, C, D, F)
      const int TO_PERCENT = 100;

      const double GradeA = 0.90;
      const double GradeB = 0.80;
      const double GradeC = 0.70;
      const double GradeD = 0.60;

      // File stream + internal state
      fstream inputFile;
      string fileName;
      string dropped;

      vector<double> calculatedPercentages;
      vector<double> averageScores;
      vector<vector<double>> calculatedClassPercentages;
      vector<vector<vector<double>>> allGrades;
      vector<int> studentIDs;     // Stores each student’s ID (1:1 with calculatedClassPercentages rows)
      vector<char> letterGrades;  // Stores each student’s final letter

      double threshold;
      int studentID;
      int classSize;
      int totalAssignmentsDropped[5];
      int totalAssignments[5];
      double gradeWeights[5]; // read from file

      bool isFileUploaded;

      /* 
         -----------------------------------------------------------
         PRIVATE UTILITY FUNCTIONS
         ----------------------------------------------------------- 
      */
      bool nonemptyLine(const std::string& line);
      double sumVector(const std::vector<double>& v);
      // static double sumVectorDropped(const std::vector<double>& v, int dropCount);

      void bubbleSort(std::vector<std::vector<double>>& classPercentages);
      void sortByStudentID();
      void sortByLetterGrade();
      void sortByTotalPerc(void);
      char letterFromTotal(double total) const;

      void getTotalPercentage(vector<vector<double>>& calculatedClassPercentages);

      void dropLowestScore(vector<vector<vector<double>>>& allGrades, int typeOfAssignment);

      void getPoints(fstream& file, vector<vector<vector<double>>>& allGrades);
      void getTotalAssignments(fstream& file, int (&totalAssignmentsArray)[5]);

      void populateGradeVector(int (&totalAssignmentAmount)[5],
                              vector<vector<vector<double>>>& allGrades,
                              int amountOfStudents);

      void populateStudentVector(int (&totalAssignmentAmount)[5],
                                 vector<vector<double>>& allGrades,
                                 int amountOfStudents);

      std::string getLetterGrade(vector<double>& calculatedPercentages);

      void calculatePercentage(double grade, double total, double gradeWeight,
                              vector<double>& calculatedPercentages);
      void computeLetterGrades(void);
      // FIXED: pass large 3D vector by const reference, not by value
      void calculateClassPercentage(const vector<vector<vector<double>>>& grade,
                                    const vector<double>& total,
                                    double gradeWeight,
                                    vector<vector<double>>& calculatedPercentages,
                                    int assignmentType);

      void getAverageOfCategory(double pointsEarned, int amountOfAssignments,
                                 vector<double>& avgOfCategory);

      void getAverageOfCategoryOfClass(const vector<vector<double>>& calculatedPercentages, int assignmentType, vector<double>& averageOfSingleCategory);

      void getIndividualStudentPointsTotal(vector<vector<vector<double>>>& allGrades, int studentNumber, vector<double>& totals);

      void getTotalScoresOfOneCategory(vector<vector<vector<double>>>& allGrades,
                                       int assignmentType,
                                       vector<vector<vector<double>>>& totalCategoryPoints);

      void readGradeWeights(std::fstream& file);

   public:

      /* 
         -----------------------------------------------------------
         CONSTRUCTORS / DESTRUCTOR
         ----------------------------------------------------------- 
      */

      calcScore();                 // default constructor
      calcScore(fstream inFile, string fileName, int studentID, int classSize);
      ~calcScore();                // destructor
      void vector_dumptruck(void); // resets major vectors


      /* 
         -----------------------------------------------------------
         MAIN FEATURES
         ----------------------------------------------------------- 
      */

      void generateReportClass(int classSize, int sortSelect, int isGradesDropped);
      void generateReportOneStudent(int isGradesDropped, int studentNumber);

      int checkFile(void) const;
      void printMenu(void);
      void fileImportFromGTK(const std::string& path);

      void printResults(void);
      void printClassResults(void);
      void printClassSortedResults(void);

      void threshScore(double threshold, int isHigh);

      std::string readRawData(void);
      void countStudentsInFile(void);

      /* 
         -----------------------------------------------------------
         DEBUGGING UTILITIES
         ----------------------------------------------------------- 
      */

      void testPrintVector(vector<vector<double>>& allGrades);


      /* 
         -----------------------------------------------------------
         SETTERS
         ----------------------------------------------------------- 
      */
      void setThreshold(int newThreshold);
      void setStudentID(int studentID);
      void setClassSize(int classSize);
      void setTotalAssignmentsDropped(int (&totalAssignmentsDropped)[5]);
      void setTotalAssignments(int (&totalAssignments)[5]);
      void setIsFileUploaded(bool);


      /* 
         -----------------------------------------------------------
         GETTERS (for GUI / charts)
         ----------------------------------------------------------- 
      */
      const std::vector<std::vector<double>>& getClassPercentages() const;
      const std::vector<double>& getAverageScores() const;
      std::string getLetterGradeSorted(const vector<double>& calculatedPercentages);
      int getClassSize() const;
      double getGradeWeight(int category) const;

};

#endif

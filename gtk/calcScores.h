/**
 * This C++ program provides functionality to read raw grade data, calculate
 * percentages, determine letter grades, drop lowest scores, sort results, and
 * generate class or single-student grade reports.
 *
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#ifndef CALCSCORES_H
#define CALCSCORES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
 * @class calcScore
 * @brief Main engine for processing and calculating student grade data.
 *
 * Responsibilities:
 * - Import raw grade files
 * - Compute category averages and total percentages
 * - Apply dropped-assignment rules
 * - Generate class and student reports
 * - Sort students by various criteria
 * - Produce formatted output for GUI and charts
 *
 * Data structures handled:
 * - 3D vectors storing raw grades
 * - Per-student calculated percentages
 * - Student IDs and final letter grades
 */
class calcScore {
   private:


      // CONSTANTS
      const int TO_PERCENT = 100;

      const double GradeA = 0.90;
      const double GradeB = 0.80;
      const double GradeC = 0.70;
      const double GradeD = 0.60;


      // INTERNAL STATE
      fstream inputFile;
      string fileName;
      string dropped;

      vector<double> calculatedPercentages;
      vector<double> averageScores;
      vector<vector<double>> calculatedClassPercentages;
      vector<vector<vector<double>>> allGrades;

      vector<int> studentIDs;
      vector<char> letterGrades;

      double threshold;
      int studentID;
      int classSize;

      int totalAssignmentsDropped[5];
      int totalAssignments[5];
      double gradeWeights[5];

      bool isFileUploaded;


      // PRIVATE UTILITY FUNCTIONS
      bool nonemptyLine(const string& line);
      double sumVector(const vector<double>& v);

      void bubbleSort(vector<vector<double>> &classPercentages);
      void sortByStudentID();
      void sortByLetterGrade();
      void sortByTotalPerc();

      char letterFromTotal(double total) const;

      void getPoints(fstream &file, vector<vector<vector<double>>> &allGrades);
      void getTotalAssignments(fstream &file, int (&arr)[5]);

      void populateGradeVector(int (&amount)[5],
                              vector<vector<vector<double>>> &allGrades,
                              int nStudents);

      void populateStudentVector(int (&amount)[5],
                              vector<vector<double>> &allGrades,
                              int nStudents);

      void readGradeWeights(fstream &file);

      void dropLowestScore(vector<vector<vector<double>>> &allGrades, int category);

      void calculatePercentage(double earned, double total, double weight,
                              vector<double> &out);

      void computeLetterGrades();

      void getAverageOfCategory(double earned, int count, vector<double>& avg);

      void getIndividualStudentPointsTotal(vector<vector<vector<double>>> &allGrades,
                              int studentNum,
                              vector<double>& totals);

      // GUI formatting helpers
      string percentToDecimal(double fraction) const;
      string padLeft(const string &s, int width) const;

   public:


      // CONSTRUCTORS / DESTRUCTOR
      calcScore();
      calcScore(fstream inFile, string fileName, int studentID, int classSize);
      ~calcScore();

      void vector_dumptruck();


      // MAIN FEATURES


      void generateReportClass(int classSize, int sortSelect, int isDropped);
      void generateReportOneStudent(int isDropped, int studentIndex);

      int checkFile() const;
      void countStudentsInFile();
      void fileImportFromGTK(const string& path);
      string readRawData();

      void threshScore(double threshold, int isHigh);


      // DEBUG
      void testPrintVector(vector<vector<double>>& allGrades);


      // SETTERS
      void setThreshold(int newThreshold);
      void setStudentID(int id);
      void setClassSize(int size);
      void setTotalAssignmentsDropped(int (&arr)[5]);
      void setTotalAssignments(int (&arr)[5]);
      void setIsFileUploaded(bool b);


      // GETTERS
      const vector<vector<double>>& getClassPercentages() const;
      const vector<double>& getAverageScores() const;

      string getLetterGradeSorted(const vector<double>& percentages);

      int getClassSize() const;
      double getGradeWeight(int category) const;

      string getClassReportString() const;
};

#endif // CALCSCORES_H

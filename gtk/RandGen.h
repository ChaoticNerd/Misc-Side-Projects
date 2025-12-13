#ifndef RANDGEN_H
#define RANDGEN_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class RandGen{
    private:
        const int QUIZ_WEIGHT = 15;
        const int LAB_WEIGHT = 15;
        const int MIDTERM_WEIGHT = 10;
        const int PROJECT_WEIGHT = 40;
        const int FINAL_EXAM_WEIGHT = 20;

        const int MAX_QUIZZES = 7;
        const int MAX_LABS = 20;
        const int MAX_MIDTERMS = 3;
        const int PROJECT_AMOUNT = 1;
        const int FINAL_EXAM_AMOUNT = 1;
        
        const int DROPPED_QUIZZES = 1;  //added dropped variables
        const int DROPPED_LABS = 2;
        const int DROPPED_MIDTERMS = 0;
        const int DROPPED_PROJECTS = 0;
        const int DROPPED_FINAL_EXAM = 0;

        const int MAX_QUIZ_SCORE = 10;
        const int MAX_LAB_SCORE = 5;
        const int MAX_MIDTERM_SCORE = 50;
        const int MAX_PROJECT_SCORE = 100;
        const int MAX_FINAL_EXAM_SCORE = 100;

        int CLASS_SIZE = 40;       // not const int, in case we they want us to change it later
        /*
        * @author: Emily Hsu
        * @param: file to write to
        * @param: maximum number of assignments possible
        * Generates the number of assignments for each category
        */
        int generateAssignmentAmount(int maxAssignments);

        /*
        * @author: Justin Narciso
        * @param: max droppable assignments
        * Generates the scores the user actually got
        */
        int generateDroppedAmount(int assignmentAmount);

        /*
        * @author: Natasha Kho
        * @param: file to write to
        * @param: maximum score possible on an assignment
        * @param: amount of iterations  
        * Generates the max possible score for each category
        */
        void generateMaxScores(ofstream& out, int maxScore, int amount);

        /*
        * @author: Natasha Kho
        * @param: file to write to
        * @param: amount of iterations
        * @param: maximum points user can get on an assignment
        * Generates the scores the user actually got
        */
        void generateScores(ofstream& out, int amount, int maxPossibleScore);

        /*
        * @author: Justin Narciso
        * @param: file to write to
        * @param: amount of iterations
        * @param: maximum points user can get on an assignment
        * Generates the scores the user actually got
        */
        void generateStudentID(ofstream& out, int studentID);

    public:
        RandGen();

        /*
        * @author: Natasha Kho
        * Outputs a file with random:
        * assignment amount, points possible per assignment, points actually earned per assignment
        */
        void generateReport(std::string fileName);
};
#endif
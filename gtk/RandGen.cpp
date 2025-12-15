/**
 * This C++ program generates randomized grade data for a class, including:
 * assignment counts, maximum scores, earned scores, and student IDs.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#include "randGen.h"
#include <cstdlib>  // rand, srand
#include <ctime>    // time


// Constructor
RandGen::RandGen() {}


// Generates a complete randomized grade report and writes it to the given file.
void RandGen::generateReport(std::string fileName) {
    int labAmount, quizAmount, midtermAmount;     // Number of assignments per category
    int droppedLabs, droppedQuizzes;

    ofstream out;
    out.open(fileName);

    // Seed the random number generator so results differ on each run
    srand(static_cast<unsigned int>(time(0)));

    // Write the weights of each category at the top of the file
    out << LAB_WEIGHT << " "
        << QUIZ_WEIGHT << " "
        << MIDTERM_WEIGHT << " "
        << PROJECT_WEIGHT << " "
        << FINAL_EXAM_WEIGHT << std::endl;

    // Generate number of assignments in each category
    labAmount     = generateAssignmentAmount(MAX_LABS);
    quizAmount    = generateAssignmentAmount(MAX_QUIZZES);
    midtermAmount = generateAssignmentAmount(MAX_MIDTERMS);

    out << labAmount      << " " << quizAmount     << " "
        << midtermAmount  << " "
        << PROJECT_AMOUNT << " "
        << FINAL_EXAM_AMOUNT << std::endl;

    // Generate dropped assignments for applicable categories
    droppedLabs    = generateDroppedAmount(labAmount);
    droppedQuizzes = generateDroppedAmount(quizAmount);

    // Values for midterms, projects, and final are currently fixed
    out << droppedLabs        << " "
        << droppedQuizzes     << " "
        << DROPPED_MIDTERMS   << " "
        << DROPPED_PROJECTS   << " "
        << DROPPED_FINAL_EXAM << std::endl;

    // Generate maximum scores for each assignment in each category
    generateMaxScores(out, MAX_LAB_SCORE,        labAmount);
    generateMaxScores(out, MAX_QUIZ_SCORE,       quizAmount);
    generateMaxScores(out, MAX_MIDTERM_SCORE,    midtermAmount);
    generateMaxScores(out, MAX_PROJECT_SCORE,    PROJECT_AMOUNT);
    generateMaxScores(out, MAX_FINAL_EXAM_SCORE, FINAL_EXAM_AMOUNT);

    out << std::endl;

    // Generate scores for each student
    for (int i = 0; i < CLASS_SIZE; i++) {
        generateStudentID(out, i);                                   // Student ID
        generateScores(out, labAmount,        MAX_LAB_SCORE);        // Labs
        generateScores(out, quizAmount,       MAX_QUIZ_SCORE);       // Quizzes
        generateScores(out, midtermAmount,    MAX_MIDTERM_SCORE);    // Midterms
        generateScores(out, PROJECT_AMOUNT,   MAX_MIDTERM_SCORE);    // Projects (uses midterm scale)
        generateScores(out, FINAL_EXAM_AMOUNT, MAX_FINAL_EXAM_SCORE); // Final

        out << std::endl;
    }

    out.close();
}


// Generates random earned scores for a given number of assignments.
// Each score is in [maxPossibleScore - 5, maxPossibleScore].
void RandGen::generateScores(ofstream& out, int amount, int maxPossibleScore) {
    int min = maxPossibleScore - 5;
    int max = maxPossibleScore;

    for (int i = 0; i < amount; i++) {
        out << (min + rand() % (max - min + 1)) << " ";
    }
}


// Writes the same maximum possible score for 'amount' assignments.
void RandGen::generateMaxScores(ofstream& out, int maxScore, int amount) {
    for (int i = 0; i < amount; i++) {
        out << maxScore << " ";
    }
}


// Randomly generates the number of assignments for a category.
int RandGen::generateAssignmentAmount(int maxAssignments) {
    int min = 1;
    int numAssignments = 0;

    return numAssignments = min + rand() % (maxAssignments - min);
}


// Randomly generates the number of dropped assignments for a category.
int RandGen::generateDroppedAmount(int assignmentAmount) {
    int numDropped = 0;

    if (assignmentAmount == 1) {
        return numDropped = 0;
    } else {
        return numDropped = rand() % assignmentAmount;
    }
}


// Outputs a zero-padded student ID of fixed width.
void RandGen::generateStudentID(ofstream& out, int studentID) {
    int width = 9;
    out << std::setfill('0') << std::setw(width) << studentID << " ";
}

/**
 * This C++ program generates randomized grade data for a class, including:
 * assignment counts, maximum scores, earned scores, and student IDs.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#ifndef RANDGEN_H
#define RANDGEN_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

/**
 * @class RandGen
 * @brief Generates randomized assignment and score data for a class grade report.
 *
 * The RandGen class outputs a structured text file containing:
 * - Assignment amounts for each category
 * - Dropped assignments
 * - Maximum possible scores per assignment
 * - Actual student scores
 * - Randomly generated student IDs
 *
 * This is primarily used for testing grade-processing programs.
 */
class RandGen {
private:
    // Weight of each grade category (percent contribution to total grade)
    const int QUIZ_WEIGHT = 15;
    const int LAB_WEIGHT = 15;
    const int MIDTERM_WEIGHT = 10;
    const int PROJECT_WEIGHT = 40;
    const int FINAL_EXAM_WEIGHT = 20;

    // Maximum number of assignments per category
    const int MAX_QUIZZES = 7;
    const int MAX_LABS = 20;
    const int MAX_MIDTERMS = 3;
    const int PROJECT_AMOUNT = 1;
    const int FINAL_EXAM_AMOUNT = 1;

    // Droppable assignments per category
    const int DROPPED_QUIZZES = 1;
    const int DROPPED_LABS = 2;
    const int DROPPED_MIDTERMS = 0;
    const int DROPPED_PROJECTS = 0;
    const int DROPPED_FINAL_EXAM = 0;

    // Maximum possible score for a single assignment
    const int MAX_QUIZ_SCORE = 10;
    const int MAX_LAB_SCORE = 5;
    const int MAX_MIDTERM_SCORE = 50;
    const int MAX_PROJECT_SCORE = 100;
    const int MAX_FINAL_EXAM_SCORE = 100;

    // Number of students to generate data for
    int CLASS_SIZE = 40;

    /**
     * @brief Generates the number of assignments for a category.
     * @param maxAssignments Maximum allowed assignments in that category.
     * @return A random integer in the valid range.
     */
    int generateAssignmentAmount(int maxAssignments);

    /**
     * @brief Determines the number of dropped assignments.
     * @param assignmentAmount Number of existing assignments.
     * @return Random number of assignments to drop.
     */
    int generateDroppedAmount(int assignmentAmount);

    /**
     * @brief Outputs maximum possible scores for a category.
     * @param out Output file stream.
     * @param maxScore Score possible per assignment.
     * @param amount Number of assignments.
     */
    void generateMaxScores(ofstream& out, int maxScore, int amount);

    /**
     * @brief Outputs randomly generated earned student scores.
     * @param out Output file stream.
     * @param amount Number of assignments.
     * @param maxPossibleScore Highest possible score for the category.
     */
    void generateScores(ofstream& out, int amount, int maxPossibleScore);

    /**
     * @brief Outputs a formatted student ID.
     * @param out Output file stream.
     * @param studentID Numeric ID of the student.
     */
    void generateStudentID(ofstream& out, int studentID);

public:
    /**
     * @brief Default constructor.
     * Generates no output; used to initialize the generator.
     */
    RandGen();

    /**
     * @brief Produces a complete randomized grade report file.
     * @param fileName Name of the text file to write.
     *
     * Output includes:
     * - Category weights
     * - Assignment counts
     * - Dropped assignments
     * - Maximum scores
     * - Actual earned scores for each student
     */
    void generateReport(std::string fileName);
};

#endif // RANDGEN_H

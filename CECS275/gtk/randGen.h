
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// make function to randomize this, i think
const int MAX_QUIZZES = 7;
const int MAX_LABS = 20;
const int MAX_MIDTERMS = 3;
const int PROJECT_AMOUNT = 1;
const int FINAL_EXAM_AMOUNT = 1;
const int MAX_QUIZ_SCORE = 10;
const int MAX_LAB_SCORE = 5;
const int MAX_MIDTERM_SCORE = 50;
const int MAX_PROJECT_SCORE = 100;
const int MAX_FINAL_EXAM_SCORE = 100;

// function prototypes
void generateScores(ofstream& out, int amount, int maxPossibleScore); 
void generateMaxScores(ofstream& out, int maxScore, int amount);

/*
 * @author: Emily Hsu
 * @param: file to write to
 * @param: maximum number of assignments possible
 * Generates the number of assignments for each category
*/
int generateAssignmentAmount(int maxAssignments){
    int min = 1, numAssignments = 0;
    return numAssignments = min + rand() % (maxAssignments - min);
}

/*
 * @author: Natasha Kho
 * @param: file to write to
 * @param: maximum score possible on an assignment
 * @param: amount of iterations  
 * Generates the max possible score for each category
*/
void generateMaxScores(ofstream& out, int maxScore, int amount){
    for(int i = 0; i < amount; i++){
        out << maxScore << " ";
    }
}

/*
 * @author: Natasha Kho
 * @param: file to write to
 * @param: amount of iterations
 * @param: maximum points user can get on an assignment
 * Generates the scores the user actually got
 */
void generateScores(ofstream& out, int amount, int maxPossibleScore){
    int min = maxPossibleScore - 5, max = maxPossibleScore;
    for(int i = 0; i < amount; i++){
        out << min + rand() % (max - min + 1) << " ";
    }
}

/*
 * @author: Natasha Kho
 * @author: Emily Hsu
 * Outputs a file with random:
 * assignment amount, points possible per assignment, points actually earned per assignment
*/
void generateReport(){
    int LAB_AMOUNT, QUIZ_AMOUNT, MIDTERM_AMOUNT;
    string fileName;
    cout << "---------------------------------------------------------\n"  
         << "Enter a name for your file ending with '.txt': " 
         << endl;
    cin >> fileName;

    ofstream out;
    out.open(fileName);
    srand(time(0)); // Ensures that each randomly generated attempt is different
    
    // Generate number of assignments in each category
    LAB_AMOUNT = generateAssignmentAmount(MAX_LABS);
    QUIZ_AMOUNT = generateAssignmentAmount(MAX_QUIZZES);
    MIDTERM_AMOUNT = generateAssignmentAmount(MAX_MIDTERMS);
    out << LAB_AMOUNT << " " << QUIZ_AMOUNT << " " << MIDTERM_AMOUNT << " " << PROJECT_AMOUNT << " " << FINAL_EXAM_AMOUNT << endl;

    // Generate max scores
    generateMaxScores(out, MAX_LAB_SCORE, LAB_AMOUNT);
    generateMaxScores(out, MAX_QUIZ_SCORE, QUIZ_AMOUNT);
    generateMaxScores(out, MAX_MIDTERM_SCORE, MIDTERM_AMOUNT);
    generateMaxScores(out, MAX_PROJECT_SCORE, PROJECT_AMOUNT);
    generateMaxScores(out, MAX_FINAL_EXAM_SCORE, FINAL_EXAM_AMOUNT);

    out << endl;

    generateScores(out, LAB_AMOUNT, MAX_LAB_SCORE); // Labs
    generateScores(out, QUIZ_AMOUNT, MAX_QUIZ_SCORE); // Quizzes
    generateScores(out, MIDTERM_AMOUNT, MAX_MIDTERM_SCORE); // Midterms
    generateScores(out, PROJECT_AMOUNT, MAX_MIDTERM_SCORE); // Projects
    generateScores(out, FINAL_EXAM_AMOUNT, MAX_FINAL_EXAM_SCORE); // Final
    
    out.close();
    cout << fileName << " generated!\n---------------------------------------------------------" << endl;

}
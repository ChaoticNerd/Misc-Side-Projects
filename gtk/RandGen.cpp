#include "randGen.h"
// Constructor
RandGen::RandGen(){}

void RandGen::generateReport(std::string fileName){
    int labAmount, quizAmount, midtermAmount;
    std::string fileLoc = "../data/"; ;
    ofstream out;

    out.open(fileLoc + fileName);
    srand(time(0)); // Ensures that each randomly generated attempt is different
    
    // Generate number of assignments in each category
    labAmount = generateAssignmentAmount(MAX_LABS);
    quizAmount = generateAssignmentAmount(MAX_QUIZZES);
    midtermAmount = generateAssignmentAmount(MAX_MIDTERMS);
    out << labAmount << " " << quizAmount << " " << midtermAmount << " " << PROJECT_AMOUNT << " " << FINAL_EXAM_AMOUNT << endl;

    // Generate max scores
    generateMaxScores(out, MAX_LAB_SCORE, labAmount);
    generateMaxScores(out, MAX_QUIZ_SCORE, quizAmount);
    generateMaxScores(out, MAX_MIDTERM_SCORE, midtermAmount);
    generateMaxScores(out, MAX_PROJECT_SCORE, PROJECT_AMOUNT);
    generateMaxScores(out, MAX_FINAL_EXAM_SCORE, FINAL_EXAM_AMOUNT);

    out << endl;

    generateScores(out, labAmount, MAX_LAB_SCORE); // Labs
    generateScores(out, quizAmount, MAX_QUIZ_SCORE); // Quizzes
    generateScores(out, midtermAmount, MAX_MIDTERM_SCORE); // Midterms
    generateScores(out, PROJECT_AMOUNT, MAX_MIDTERM_SCORE); // Projects
    generateScores(out, FINAL_EXAM_AMOUNT, MAX_FINAL_EXAM_SCORE); // Final
    
    out.close();
}

void RandGen::generateScores(ofstream& out, int amount, int maxPossibleScore){
    int min = maxPossibleScore - 5, max = maxPossibleScore;
    for(int i = 0; i < amount; i++){
        out << min + rand() % (max - min + 1) << " ";
    }
}

void RandGen::generateMaxScores(ofstream& out, int maxScore, int amount){
    for(int i = 0; i < amount; i++){
        out << maxScore << " ";
    }
}

int RandGen::generateAssignmentAmount(int maxAssignments){
    int min = 1, numAssignments = 0;
    return numAssignments = min + rand() % (maxAssignments - min);
}
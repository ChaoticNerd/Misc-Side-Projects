#include "randGen.h"
// Constructor
RandGen::RandGen(){}

void RandGen::generateReport(std::string fileName){
    int labAmount, quizAmount, midtermAmount; // max assignments per category
    int droppedLabs, droppedQuizzes;
    //int classSize = 40;
    //std::string fileLoc = "../data/"; ;
    ofstream out;

    out.open(fileName);
    srand(time(0)); // Ensures that each randomly generated attempt is different
    //add the weights of each category at the top of the file
    out << LAB_WEIGHT << " " << QUIZ_WEIGHT << " " << MIDTERM_WEIGHT << " " << PROJECT_WEIGHT << " " << FINAL_EXAM_WEIGHT << endl;


    // Generate number of assignments in each category
    labAmount = generateAssignmentAmount(MAX_LABS);
    quizAmount = generateAssignmentAmount(MAX_QUIZZES);
    midtermAmount = generateAssignmentAmount(MAX_MIDTERMS);
    out << labAmount << " " << quizAmount << " " << midtermAmount << " " << PROJECT_AMOUNT << " " << FINAL_EXAM_AMOUNT << endl;

    // Generate Dropped assignments for each category (added by the Oracle Justine)
    droppedLabs = generateDroppedAmount(labAmount);
    droppedQuizzes = generateDroppedAmount(quizAmount);  
    // Set up in case we want to add dropped assignments for midterms/projects/finals later
    // generateDroppedAmount(midtermAmount);
    // generateDroppedAmount(PROJECT_AMOUNT);
    // generateDroppedAmount(FINAL_EXAM_AMOUNT);
    out << droppedLabs << " " << droppedQuizzes << " " << DROPPED_MIDTERMS << " " << DROPPED_PROJECTS << " " << DROPPED_FINAL_EXAM << endl; 

    // Generate max scores
    generateMaxScores(out, MAX_LAB_SCORE, labAmount);
    generateMaxScores(out, MAX_QUIZ_SCORE, quizAmount);
    generateMaxScores(out, MAX_MIDTERM_SCORE, midtermAmount);
    generateMaxScores(out, MAX_PROJECT_SCORE, PROJECT_AMOUNT);
    generateMaxScores(out, MAX_FINAL_EXAM_SCORE, FINAL_EXAM_AMOUNT);

    out << endl;

    for (int i = 0; i < CLASS_SIZE; i++){
        generateStudentID(out, i);
        generateScores(out, labAmount, MAX_LAB_SCORE); // Labs
        generateScores(out, quizAmount, MAX_QUIZ_SCORE); // Quizzes
        generateScores(out, midtermAmount, MAX_MIDTERM_SCORE); // Midterms
        generateScores(out, PROJECT_AMOUNT, MAX_MIDTERM_SCORE); // Projects
        generateScores(out, FINAL_EXAM_AMOUNT, MAX_FINAL_EXAM_SCORE); // Final
        
        out << endl;
    }
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

int RandGen::generateDroppedAmount(int assignmentAmount){
    int numDropped = 0;
    if (assignmentAmount == 1)
        return numDropped = 0;
    else
        return numDropped = rand() % (assignmentAmount);
}

void RandGen::generateStudentID(ofstream& out, int studentID){
    int width = 9;
    out << std::setfill('0') << std::setw(width) << studentID <<" ";

}
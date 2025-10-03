#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#include "calcScores.h"

// Function prototype for testPrintVector
void testPrintVector(vector<vector<vector<double>>> &allGrades);

int main(void){
    fstream input;
    //input.open("scores.txt");
    input.open("new_scores.txt");

    int totalAssignments[5];
    int totalAssignmentsDropped[5];
    vector<double> calculatedPercentages;
    vector<double> averageScore;

    //  rows go in such fashion:
    //  * all total lab/quiz/exam/project points
    //  * first students' grades
    //  * second students' grades
    //  * and so on and so on
    vector<vector<vector<double>>> allGrades;
    vector<double> individualStudentScores;
// First line of file
    getTotalAssignments(input,totalAssignments);

    getTotalAssignments(input,totalAssignmentsDropped);

    populateGradeVector(totalAssignments, allGrades, 40);

    getPoints(input, totalAssignments, allGrades);
    // testPrintVector(allGrades);

    // used for calculations
    double totalCategoryPoints[40][5][1];
    vector<double> totalPointsPossible;

    // Do the stuff to drop the lowest grade as per requested wahoo!
    for(int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
        int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
        while(amtOfAssignmentsToDrop){
            dropLowestScore(input, allGrades,i);
            amtOfAssignmentsToDrop--;
        }
    }
      // generateReportClass(input, allGrades, totalAssignmentsDropped, totalAssignments, 0, 1, calculatedPercentages,averageScore);
    //printResults(calculatedPercentages,averageScore);
        cout << "==============================================" << endl;
    for(int i = 0; i < 5; i++){ // goes for amount of categories there are
        getTotalScoresOfOneCategory(allGrades, totalAssignments, i, totalCategoryPoints); // student score is totalEarnedPoints
    }
    getIndividualStudentPointsTotal(allGrades, 0, totalAssignments, totalPointsPossible);
    
    // this calculates the percentages for one student
    //  calculatePercentage(double grade, double total, double gradeWeight, vector<double> &calculatedPercentages)
    // this part requires testing
    for(int i = 0; i < allGrades.size() - 1; i++){ // this needs to iterate 40 times
        for(int j = 0; j < sizeof(totalAssignments)/sizeof(totalAssignments[0]); j++){ // iterates 5 times

            // what does one run through of this mean?
            calculatePercentage(totalCategoryPoints[i][j][0], totalPointsPossible[j], gradeWeights[j], calculatedPercentages);
            
            // average scores should be size 5 vector
            getAverageOfCategory(totalCategoryPoints[i][j][0], totalAssignments[j], averageScore);
        }
    }
    cout << calculatedPercentages.size() << endl;
    cout << "PERCENTAGES: " << endl;
    for(double x : calculatedPercentages){
        cout << x << " " << endl;
    }
    return 1;
}

void testPrintVector(vector<vector<vector<double>>> &allGrades){
    for(int i = 0; i < allGrades.size(); i++){
        for(int j = 0; j < allGrades[i].size(); j++){
            for(int k = 0; k < allGrades[i][j].size(); k++){
                cout << allGrades[i][j][k] << " ";
            }
        }
        cout << endl;
    }
}
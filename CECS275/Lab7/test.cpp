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
    ////////////////////////////////////////////////////////////////////////////////////////////
    // fstream &inputFile, vector<vector<vector<double>>> &allGrades, int (&totalAssignmentsDropped)[5], int (&totalAssignments)[5], 
    //                   int isGradesDropped, vector<vector<double>> &calculatedPercentages, vector<double> &averageScores){
    vector<vector<vector<double>>> allGrades;
    int totalAssignmentsDropped[5];
    int totalAssignments[5];
    vector<vector<double>> calculatedPercentages;
    vector<double> averageScores;

    int fuckMyStupidBakaLife[5] = {1, 1, 1, 1, 1};
    
    // INDIVIDUAL STUDENT SCORE
    // First line of file
    getTotalAssignments(input,totalAssignments);
    // for(int val: totalAssignments){
    //     cout << "Total Assignments: " << val  << endl;
    // }

    // Have a function to get amount of quiz/labs dropped
    getTotalAssignments(input,totalAssignmentsDropped);
    // for(int val: totalAssignmentsDropped){
    //     cout << "Total Assignments Dropped: " << val  << endl;
    // }

    // cout << "===========================================\nPOPULATING POINTS POSSIBLE VECTOR" << endl;
    populateGradeVector(totalAssignments, allGrades, 40);
    // testPrintVector(allGrades); // should be a buncha 0s

    // cout << "===========================================\nINPUTTING POINTS" << endl;
    getPoints(input, totalAssignments, allGrades);
    // testPrintVector(allGrades); // PLEASE PRINT NUMBERS PLEAAAAAAASE

    // used for calculations
    vector<double> totalEarned;
    vector<double> totalPointsPossible;


    // Do the stuff to drop the lowest grade as per requested wahoo!
    for(int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
    int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
        while(amtOfAssignmentsToDrop){
            //cout << "AT I: " << i << " ASSIGNMENT TO BE DROPPED DETECTED ::: " << totalAssignmentsDropped[i] << endl;
            dropLowestScore(input, allGrades,i );
            amtOfAssignmentsToDrop--;
            totalAssignments[i]--;
        }
    }

    
    getIndividualStudentPointsTotal(allGrades, 5, totalAssignments, totalEarned); // student score is totalEarnedPoints
    getIndividualStudentPointsTotal(allGrades, 0, totalAssignments, totalPointsPossible);
    cout << totalEarned.size() << endl;
    
    for(int i = 0; i < totalEarned.size(); i++){
        //calculatePercentage(totalEarned[i], totalPointsPossible[i], gradeWeights[i], calculatedPercentages);
        getAverageOfCategory(totalEarned[i], totalAssignments[i], averageScores);
        cout << "Current grade weight: " << gradeWeights[i] << endl;
    }
    
    cout << "CHECKING CALCULATED PERCENTAGES" << endl;
    for(double x: calculatedPercentages){
        cout << x << " ";
    }
    cout << endl;
    
    cout << "CHECKING AVERAGE SCORES" << endl;
    for(double x: averageScores){
        cout << x << " ";
    }
    cout << endl;
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
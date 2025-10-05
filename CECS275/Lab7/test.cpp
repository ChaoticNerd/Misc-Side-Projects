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
    
    // First line of file
    getTotalAssignments(input,totalAssignments);

    getTotalAssignments(input,totalAssignmentsDropped);

    populateGradeVector(totalAssignments, allGrades, 40);

    getPoints(input, totalAssignments, allGrades);

    // used for calculations 
    vector<vector<vector <double>>> totalCategoryPoints;
    vector<double> totalPointsPossible;

    // Do the stuff to drop the lowest grade as per requested wahoo!
    for(int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
        int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
        while(amtOfAssignmentsToDrop){
            dropLowestScore(input, allGrades,i);
            totalAssignments[i]--;
            amtOfAssignmentsToDrop--;
        }
    }
    cout << "TEST0" << endl;

    populateGradeVector(fuckMyStupidBakaLife, totalCategoryPoints, 39);
    // testPrintVector(totalCategoryPoints);
    populateStudentVector(fuckMyStupidBakaLife, calculatedPercentages, 39);

    for(int i = 0; i < 5; i++){ // goes for amount of categories there are
        getTotalScoresOfOneCategory(allGrades, totalAssignments, i, totalCategoryPoints); // student score is totalEarnedPoints
    }
    //testPrintVector(totalCategoryPoints);
    getIndividualStudentPointsTotal(allGrades, 0, totalAssignments, totalPointsPossible);

    // testPrintVector(allGrades);
    // for(double x: totalPointsPossible){
    //     cout << "SEEING INSIDE TOTAL POINTS POSSIBLE: " << x <<endl;
    // }
    // this calculates the percentages for one student
    //  calculatePercentage(double grade, double total, double gradeWeight, vector<double> &calculatedPercentages)
    // this part requires testing
    for(int i = 0; i < allGrades.size() - 1; i++){ // this needs to iterate 40 times
        for(int j = 0; j < sizeof(totalAssignments)/sizeof(totalAssignments[0]); j++){ // iterates 5 times
            calculateClassPercentage(totalCategoryPoints, totalPointsPossible, gradeWeights[j], calculatedPercentages, j);
            //cout << "COUNT: (" << i << " , " << j << ")  "<<calculatedPercentages[i][j]<< endl;
            // average scores should be size 5 vector

            // you pass in calculatedPercentages
            // and inside of get avg, you iterate through assigmnent type again
            
        }
    }
    for(int i = 0; i < sizeof(totalAssignments)/sizeof(totalAssignments[0]); i++){
        getAverageOfCategoryOfClass(calculatedPercentages, i, averageScores);
        // cout << "AVG SCORES: (" << i << " , " << j << ") "<< averageScores[i] <<endl; 
    }
    // cout << "amount of Average Scores: " << averageScores.size()<< endl; 
    // cout << "PERCENTAGES: " << endl;
    // for(int i = 0; i < calculatedPercentages.size(); i++){
    //     for(double x : calculatedPercentages[i]){
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }

    cout << "AverageScores: " << endl;
    for(double avgs : averageScores){
        cout << avgs << " ";
    }
    cout  << endl;
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
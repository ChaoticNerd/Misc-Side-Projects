#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#include "calcScores.h"

const int classSize = 40;

// Function prototypes for testPrintVector
void testPrintVector(vector<vector<double>> &allGrades);
void testPrintVector(vector<vector<vector<double>>> &allGrades);

int main(void){
    fstream input;
    //input.open("scores.txt");
    input.open("new_scores.txt");
    ////////////////////////////////////////////////////////////////////////////////////////////

    vector<vector<vector<double>>> allGrades;
    int totalAssignmentsDropped[5];
    int totalAssignments[5];
    vector<vector<double>> calculatedPercentages;
    vector<double> averageScores;

    int fuckMyStupidBakaLife[5] = {1, 1, 1, 1, 1};

    // used for calculations
    vector<vector<vector <double>>> totalCategoryPoints;
    vector<double> totalPointsPossible;
    int temp[5] = {1, 1, 1, 1, 1};

    // First line of file
    getTotalAssignments(input,totalAssignments);

    getTotalAssignments(input,totalAssignmentsDropped);

    populateGradeVector(totalAssignments, allGrades, classSize);

    getPoints(input, totalAssignments, allGrades);

    populateGradeVector(temp, totalCategoryPoints, classSize-1);
    populateStudentVector(temp, calculatedPercentages, classSize-1);    
    
    // Do the stuff to drop the lowest grade as per requested wahoo!
    for(int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
        int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
        while(amtOfAssignmentsToDrop){
            dropLowestScore(input, allGrades,i);
            amtOfAssignmentsToDrop--;
            totalAssignments[i]--;
        }
    }
    

    // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS" << endl; THIS PRINTS
    
    for(int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){ // goes for amount of categories there are
        getTotalScoresOfOneCategory(allGrades, totalAssignments, i, totalCategoryPoints); // student score is totalEarnedPoints
    }


    getIndividualStudentPointsTotal(allGrades, 0, totalAssignments, totalPointsPossible);
    // cout << "before grade totalScores\n";
    // testPrintVector(allGrades);
    // for(double x: totalPointsPossible){
    //     cout << "SEEING INSIDE TOTAL POINTS POSSIBLE: " << x <<endl;
    // }

    // TODO: THIS PART BREAKS
    // this calculates the percentages for one student
    //  calculatePercentage(double grade, double total, double gradeWeight, vector<double> &calculatedPercentages)
    // this part requires testing
    for(int i = 0; i < allGrades.size() - 1; i++){ // this needs to iterate 40 times
        for(int j = 0; j < sizeof(totalAssignments)/sizeof(totalAssignments[0]); j++){ // iterates 5 times
            // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS 0" << endl; // THIS PRINTS

            calculateClassPercentage(totalCategoryPoints, totalPointsPossible, gradeWeights[j], calculatedPercentages, j);
            // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS 1" << endl; // THIS PRINTS
            //cout << "COUNT: (" << i << " , " << j << ")  "<<calculatedPercentages[i][j]<< endl;
            // average scores should be size 5 vector
        }
    }
    // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS" << endl; // THIS PRINTS

    for(int i = 0; i < sizeof(totalAssignments)/sizeof(totalAssignments[0]); i++){
        getAverageOfCategoryOfClass(calculatedPercentages, i, averageScores);
        // cout << "AVG SCORES: (" << i << " , " << j << ") "<< averageScores[i] <<endl; 
    }
    cout << "GETTING TOTAL PERCENTAGES" << endl;
    getTotalPercentage(calculatedPercentages);
    testPrintVector(calculatedPercentages);

    cout << "========================================================\n"
         << "TESTING BUBBLE SORT" << endl;
    bubbleSort(calculatedPercentages);
    testPrintVector(calculatedPercentages);


    double thoughts = .80;
    int isHigh = 1;

    cout << "========================================================\n"
         << "TESTING THRESHOLD DISPLAYED" << endl;
    threshScore(calculatedPercentages,thoughts,isHigh);
    testPrintVector(calculatedPercentages);
    // cout << "amount of Average Scores: " << averageScores.size()<< endl; 
    // cout << "PERCENTAGES: " << endl;, 
    // for(int i = 0; i < calculatedPercentages.size(); i++){
    //     for(double x : calculatedPercentages[i]){
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "AverageScores: " << endl;
    // for(double avgs : averageScores){
    //     cout << avgs << " ";
    // }
    // cout  << endl;
    
}

void testPrintVector(vector<vector<double>> &allGrades){
    for(int i = 0; i < allGrades.size(); i++){
        for(int j = 0; j < allGrades[i].size(); j++){
                cout << allGrades[i][j] << " ";
            
        }
        cout << endl;
    }
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
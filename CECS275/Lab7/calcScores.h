/*
 * Header files where calculations are done
 * @author: Natasha Kho
 * @author: Emily Hsu
 * Created on: 2025-09-11
 * Last Modified: 2025-09-15
 * Reference: 
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include "randGen.h"

// Function prototypes
void printMenu(int userSelect);
void generateReport(string fileName);
void printResults(double projectGrade, double labGrade, 
                    double quizGrade, double examGrade, double finalGrade, 
                    double totalGrade, char letterGrade);
void generateReportClass(fstream &inputFile, vector<vector<vector<double>>> &allGrades, int (&totalAssignmentsDropped)[5], int (&totalAssignments)[5], 
        int isGradesDropped, vector<double> &calculatedPercentages, vector<double> &averageScores);
void vector_dumptruck(vector<double> &calculatedPercentages, vector<double> &averageScores,
                      vector<vector<double>> &calculatedClassPercentages, vector<vector<vector<double>>> &allGrades);

using namespace std;

// Grade weights
const double gradeWeights[5] = {0.15, 0.15, .40, 0.10, 0.20};

// Converts fractional value to percentage
const int TO_PERCENT = 100;
const double GradeA = 0.90,
             GradeB = 0.80,
             GradeC = 0.70,
             GradeD = 0.60;

/*
 * @author Natasha Kho
*/
void dropLowestScore(fstream& file,vector<vector<vector<double>>> (&allGrades), int typeOfAssignment){
    //int lowestScore = 0x7FFFFFFF; // this is the maximum int in hex

    // this iterates through all the students (41 total)
    for(int i = 0; i < allGrades.size(); i++ ){

        // this iterates through a student's assignment categories (5 total)
        for(int j = typeOfAssignment; j < allGrades[i].size(); j++){
            // cout << "function called" << endl;
            int indexToDrop = 0;     

            // cout << "STARTING NEW ITERATION: " << j << endl;

            // this iterates through a student's assignment's grades 
            // (ie. lab grades, then quiz grades, then exam grades, etc.)
            for(int k = 0; k < allGrades[i][j].size(); k++){
                // cout << "Where is K going: " << k << endl;
                // cout << allGrades[i][j].size() << " is the size of this shit." << endl;
                // if all of the current values of indexesToDrop are lower than the current value of allGrades, 
                // then it's added to get dropped
                if(allGrades[i][typeOfAssignment][indexToDrop] > allGrades[i][typeOfAssignment][k]){
                    // cout << "SETTING NEW K: " << k << endl;
                    indexToDrop = k;
                }
                
            }    
            //cout << "ERASING AT INDEX: " << indexToDrop << " WITH VALUE: " << allGrades[i][typeOfAssignment][indexToDrop] << endl;    
            // cout << "type of assignment: " << typeOfAssignment << endl;
            // cout << "FUCK " << allGrades[i][typeOfAssignment][indexToDrop] << endl;

            allGrades[i][typeOfAssignment].erase(allGrades[i][typeOfAssignment].begin() + indexToDrop);   
            break;
        }
    }
    
}

/*
 * @author: Natasha Kho
 * @param: filestream file variable
 * @param: amount of assignments to iterate through
 * @return total score of one category of assignment
*/
void getPoints(fstream& file, int (&totalAssignmentAmount)[5], vector<vector<vector<double>>> &allGrades){
    double temp;
    for(int i = 0; i < allGrades.size(); i++){
        for(int j = 0; j < allGrades[i].size(); j++){
            for(int k = 0; k < allGrades[i][j].size(); k++){
                file >> allGrades[i][j][k];
            }
        }
    }
    // for(int i = 0; i < totalAssignmentAmount; i++){
    //     file >> totalScoreArray[i];
    // }
}

/*
 * @author: Natasha Kho
 * @param: filestream file variable
 * @param: reference integer array of length 5
*/
void getTotalAssignments(fstream& file, int (&totalAssignmentsArray)[5]){
    // First line of file
    for(int i = 0; i < 5; i++ ){
        file >> totalAssignmentsArray[i];
    }
    
}

/*
 * @author Natasha Kho
*/
void populateGradeVector(int (&totalAssignmentAmount)[5], vector<vector<vector<double>>> &allGrades, int amountOfStudents){
    for(int i = 0; i < amountOfStudents + 1; i++){ // iterate 40 times because 40 students
        vector<vector<double>> studentScore; // Students' scores
        for(int j = 0; j < 5; j++){ // iterate 5 times because 5 categories per student
            vector<double> individualGrades;
            for(int k = 0; k < totalAssignmentAmount[j]; k++){ // iterates through amount of grades for each category
                individualGrades.push_back(0);
                // cout << individualGrades[k] << ' ';
            }
            studentScore.push_back(individualGrades);
            // cout << endl;
        }
         allGrades.push_back(studentScore); // pushing data for one student
                                            // allGrades[i] = push back needs to contain vector<vector<double>
    }
}

/*
 * @author Natasha Kho
 * overloaded
*/
void populateStudentVector(int (&totalAssignmentAmount)[5], vector<vector<double>> &allGrades, int amountOfStudents){
    for(int i = 0; i < amountOfStudents + 1; i++){ // iterate 40 times because 40 students
        vector<double> studentScore; // Students' scores
        //cout << "Woah How many Students?!?!: " << i << "   ";
        for(int j = 0; j < 5; j++){ // iterate 5 times because 5 categories per student
            
            studentScore.push_back(0);
            // cout << studentScore[j] << ' ';
        }
        // cout << endl;
        allGrades.push_back(studentScore); // pushing data for one student
                                            // allGrades[i] = push back needs to contain vector<vector<double>
    }
}

/*
 * @author: Natasha Kho
 * @param: total grade after calculations
 * @return letter grade based on score
*/
std::string getLetterGrade(vector<double> &calculatedPercentages){
    double totalGrade;
    for(int i = 0; i < calculatedPercentages.size(); i++){
        totalGrade += calculatedPercentages[i];
    }
    // cout << "Total Grade: " << totalGrade <<endl;
    calculatedPercentages.push_back(totalGrade);

    if (totalGrade >= GradeA) {
        return "A";
    } else if (totalGrade >= GradeB){
        return "B";
    } else if (totalGrade >= GradeC){
        return "C";
    } else if (totalGrade >= GradeD){
        return "D";
    } else {
        return "F";
    }
}

/*
 * @author: Natasha Kho
 * @param: actual points earned on total assignmenets
 * @param: total amount of points possible on assignment type
 * @return percentage of specific category
*/
void calculatePercentage(double grade, double total, double gradeWeight, vector<double> &calculatedPercentages){
    // cout << "\nGrade we're inputting: " <<  grade
    //      << "\nTotal we're inputting: " << total << endl;
    calculatedPercentages.push_back((grade/total)*gradeWeight);
}

/*
 * @author: Natasha Kho
 * secret second author
*/
void calculateClassPercentage(vector<vector<vector<double>>> grade, vector<double> total, double gradeWeight, vector<vector<double>> &calculatedPercentages, int assignmentType){
    // we need a temp variable that calculates all the quiz or lab or whatever grade
    // and then, push that into the calculated percentages double array  
    double forklift = 0;
    // cout <<"student amt: "<< grade.size() << " category: "<< grade[0].size() << endl;
    for (int i = 0; i < grade.size(); i++){ // 40 iterations
        forklift = 0;
        for (int j = 0; j < grade[i].size(); j++){ //  5 iterations
            for (int k = 0; k < grade[i][j].size(); k++){ // amt of assignments
                // cout << "fork life lift error check :total check: " << grade[i][assignmentType][k] <<  endl;
                forklift += grade[i][assignmentType][k] / total[assignmentType] * gradeWeight;
                // cout << "EYE TRACKER: " << i << endl;
            }
            // cout << " ASS DID I????" << endl;
            // cout << "CHECKING CALC PRECENTG " <<  calculatedPercentages[i][assignmentType] << endl;
            calculatedPercentages[i].at(assignmentType) = forklift; //40 x 5
            
            // cout << "What's on the lift!! " << forklift <<endl;
            // cout << "what Gibby thinkin about (calcpercentage[i]): " << calculatedPercentages[i][assignmentType] << endl;
           
            break;
            //cout << "what (i,j) CalcPercent:  (" << i << " " << j << ") " << calculatedPercentages[i][j] << endl; 

        }
        //calculatedPercentages[studentTrack].at(assignmentType) = forklift;
        //cout << "TELL ME YOUR SECRETS CALCULATED PERCENT[i][0-4]:  " << calculatedPercentages[studentTrack][0] << " " << calculatedPercentages[studentTrack][1] << " "<< calculatedPercentages[studentTrack][2] << " "<< calculatedPercentages[studentTrack][3] << " "<< calculatedPercentages[studentTrack][4] << " " <<endl;
    }

    // cout << "CHECKING CALCULATED PERCENTAGES" << endl;
    // for(int i = 0; i < calculatedPercentages.size(); i++){
    //     for(double x: calculatedPercentages[i]){
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }

    // far far outside, you have the push_back
}

/*
 * @author: Natasha Kho
 * for single student usage
*/
void getAverageOfCategory(double pointsEarned, int amountOfAssignments, vector<double> &averageOfSingleCategory){
    averageOfSingleCategory.push_back(pointsEarned/amountOfAssignments);
}

/*
 * @author: Natasha Kho
 * for class average
*/
void getAverageOfCategoryOfClass(vector<vector<double>> calculatedPercentages, int assignmentType, vector<double> &averageOfSingleCategory){
    double pointsEarned = 0; 
    for (int i = 0; i < calculatedPercentages.size(); i++){
        pointsEarned += calculatedPercentages[i][assignmentType];
    }
    
    averageOfSingleCategory.push_back(pointsEarned/40);
}

/*
 * @author: Natasha Kho
 * returns totalEarnedPoints (which is points earned in each category)
*/
void getIndividualStudentPointsTotal(vector<vector<vector<double>>> &allGrades, int studentNumber, int (&totalAssignments)[5], vector<double> &totalEarnedPoints){
    vector<double> oneStudentScore;
    for(int i = studentNumber; i < allGrades.size(); i++){
        for(int j = 0; j < allGrades[studentNumber].size(); j++){
            for(int k = 0; k < allGrades[i][j].size(); k++){
                oneStudentScore.push_back(allGrades[studentNumber][j][k]);
            }
        }
        break;
    }

    // this totals the points earned in each category by the student 
    int cursor = 0;
    for(int assignmentInCategory: totalAssignments){
        double temp = 0;;
        //cout << "\nAssignment amount in Category: " << assignmentInCategory << endl;
        for(int i = 0; i < assignmentInCategory; i++){
            temp += oneStudentScore[cursor];
            cursor++;
        }
        totalEarnedPoints.push_back(temp);
    }
}

void getTotalScoresOfOneCategory(vector<vector<vector<double>>> &allGrades, int (&totalAssignments)[5], int assignmentType, vector<vector<vector<double>>> &totalCategoryPoints){
    vector<double> pointsEarnedForOneCategory;
    double temp = 0;
    //cout << "TEST1" << endl;
    for(int i = 1; i < allGrades.size(); i++){
        for(int j = 0; j < allGrades[assignmentType].size(); j++){
            for(int k = 0; k < allGrades[i][assignmentType].size(); k++){
                // cout << "TEST " << k << endl;
                temp += allGrades[i][assignmentType][k]; // adds each score of one category
                // cout << allGrades[i][assignmentType][k] << " + ";
            }
            // cout << "Total score of category: " << assignmentType << " is: " << temp << endl;

            pointsEarnedForOneCategory.push_back(temp); // puts total of one category into vector;
            temp = 0;
            break;
        }
    }

    // cout << "CHECKING POINTS EARNED FOR ONE CATEGORY VECTOR: " <<endl;
    // for(double x: pointsEarnedForOneCategory){
    //     cout << x << " ";
    // }
    // cout << endl;

    // cout << "Finish first for loop " << endl;

    // Sudo code to put into 3d vector of scores
    for(int i = 0; i < allGrades.size()-1; i++){ // this runs 40 times
        // cout << "Enter second for loop " << allGrades.size()-1 << endl;
        // cout << "Points earned in category vector: " << pointsEarnedForOneCategory[i] << endl;
        totalCategoryPoints[i][assignmentType].at(0) = pointsEarnedForOneCategory[i]; // this is not working correctly

        // totalCategoryPoints size is: 40 : 5 : 1
        // cout << "After putting data into Total Earned Points: " << totalCategoryPoints[i][assignmentType][1] <<endl;
        // line above states that we're putting in 0s only

    }
}

/*
 * @author: Natasha Kho
*/
void generateReportClass(fstream &inputFile, int classSize, vector<vector<vector<double>>> &allGrades, int (&totalAssignmentsDropped)[5], int (&totalAssignments)[5], 
                         int isGradesDropped, vector<vector<double>> &calculatedPercentages, vector<double> &averageScores){
    // used for calculations
    vector<vector<vector <double>>> totalCategoryPoints;
    vector<double> totalPointsPossible;
    int temp[5] = {1, 1, 1, 1, 1};

    // First line of file
    getTotalAssignments(inputFile,totalAssignments);

    getTotalAssignments(inputFile,totalAssignmentsDropped);

    populateGradeVector(totalAssignments, allGrades, classSize);

    getPoints(inputFile, totalAssignments, allGrades);

    populateGradeVector(temp, totalCategoryPoints, 39);
    populateStudentVector(temp, calculatedPercentages, 39);    
    if(isGradesDropped){
        // Do the stuff to drop the lowest grade as per requested wahoo!
        for(int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
            int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
            while(amtOfAssignmentsToDrop){
                dropLowestScore(inputFile, allGrades,i);
                amtOfAssignmentsToDrop--;
                totalAssignments[i]--;
            }
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

            // this breaks on index 0
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
    // cout << "amount of Average Scores: " << averageScores.size()<< endl; 
    // cout << "PERCENTAGES: " << endl;
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

void generateReportOneStudent(fstream &inputFile, vector<vector<vector<double>>> &allGrades, int (&totalAssignmentsDropped)[5], int (&totalAssignments)[5], int isGradesDropped, int studentNumber, vector<double> &calculatedPercentages, vector<double> &averageScores){
    // First line of file
    getTotalAssignments(inputFile,totalAssignments);
    // for(int val: totalAssignments){
    //     cout << "Total Assignments: " << val  << endl;
    // }

    // Have a function to get amount of quiz/labs dropped
    getTotalAssignments(inputFile,totalAssignmentsDropped);
    // for(int val: totalAssignmentsDropped){
    //     cout << "Total Assignments Dropped: " << val  << endl;
    // }

    // cout << "===========================================\nPOPULATING POINTS POSSIBLE VECTOR" << endl;
    populateGradeVector(totalAssignments, allGrades, 40);
    // testPrintVector(allGrades); // should be a buncha 0s

    // cout << "===========================================\nINPUTTING POINTS" << endl;
    getPoints(inputFile, totalAssignments, allGrades);
    // testPrintVector(allGrades); // PLEASE PRINT NUMBERS PLEAAAAAAASE

    // used for calculations
    vector<double> totalEarned;
    vector<double> totalPointsPossible;

    if(isGradesDropped){
        // Do the stuff to drop the lowest grade as per requested wahoo!
        for(int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
        int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
            while(amtOfAssignmentsToDrop){
                //cout << "AT I: " << i << " ASSIGNMENT TO BE DROPPED DETECTED ::: " << totalAssignmentsDropped[i] << endl;
                dropLowestScore(inputFile, allGrades,i );
                amtOfAssignmentsToDrop--;
                totalAssignments[i]--;
            }
        }
    }
    getIndividualStudentPointsTotal(allGrades, studentNumber, totalAssignments, totalEarned); // student score is totalEarnedPoints
    getIndividualStudentPointsTotal(allGrades, 0, totalAssignments, totalPointsPossible);

    for(int i = 0; i < totalEarned.size(); i++){
        calculatePercentage(totalEarned[i], totalPointsPossible[i], gradeWeights[i], calculatedPercentages);
        getAverageOfCategory(totalEarned[i], totalAssignments[i], averageScores);
    }

    // // debug loop
    //         cout << "Viewing Calculated Percentages" << endl;
    //         cout << calculatedPercentages.size() << endl;
    //         for(double x : calculatedPercentages){
    //             cout << x << " ";
    //         }
    //         cout << endl;

    //         cout << "Viewing Average Scores" << endl;
    //         cout << averageScores.size() << endl;
    //         for(double x : averageScores){
    //             cout << x << " ";
    //         }
    //         cout << endl;
    // end debug loop
}

void vector_dumptruck(
    vector<double> &calculatedPercentages, vector<double> &averageScores,
    vector<vector<double>> &calculatedClassPercentages,
    vector<vector<vector<double>>> &allGrades){
        calculatedPercentages.clear();
        averageScores.clear();
        calculatedClassPercentages.clear();
        allGrades.clear();
}

/*
 * @author Natasha Kho
 * couts the report
 * @param: weighted project grade as decimal
*/
void printResults(vector<double> calculatedPercentages, vector<double> averageScores){
    string letterGrade = getLetterGrade(calculatedPercentages);

    // // debug loop
    // cout << "Viewing Calculated Percentages" << endl;
    // for(double x : calculatedPercentages){
    //     cout << x << " ";
    // }
    // cout << endl;

    // cout << "Viewing Average Scores" << endl;
    // for(double x : averageScores){
    //     cout << x << " ";
    // }
    // cout << endl;

    cout << "===============================================\n" << setw(20) << "GRADES"           << "\n"
    << "Project: "      << setw(23) << fixed << setprecision(2) << calculatedPercentages[3] * TO_PERCENT    << "%\n" 
    << "Lab: "          << setw(27)                             << calculatedPercentages[0] * TO_PERCENT    << "%\n"
    << "Quiz: "         << setw(26)                             << calculatedPercentages[1] * TO_PERCENT    << "%\n"
    << "Exams: "        << setw(25)                             << calculatedPercentages[2] * TO_PERCENT    << "%\n"
    << "Final Exam: "   << setw(20)                             << calculatedPercentages[4] * TO_PERCENT    << "%\n"
    << "Total: "        << setw(25)                             << calculatedPercentages[5] * TO_PERCENT    << "%\n"
    << "Final Letter Grade: " << setw(10)                       << letterGrade                              << "\n"
    << "===============================================\n" << endl;

    cout << "===============================================\n" << setw(25) << "AVERAGE GRADES" << "\n"
    << "Project: "      << setw(23) << fixed << setprecision(2) << averageScores[3]             << "%\n" 
    << "Lab: "          << setw(27)                             << averageScores[0]             << "%\n"
    << "Quiz: "         << setw(26)                             << averageScores[1]             << "%\n"
    << "Exams: "        << setw(25)                             << averageScores[2]             << "%\n"
    << "Final Exam: "   << setw(20)                             << averageScores[4]             << "%\n"
    << "===============================================\n" << endl;
}

/*
 * @author Natasha Kho
*/
void printClassResults(vector<double> classAvg){
    double totalAvg;
    for(double x: classAvg){
        totalAvg += x;
    }
    
    cout << "===============================================\n" << setw(25) << "CLASS AVERAGES" << "\n"
    << "Project: "      << setw(23) << fixed << setprecision(2) << classAvg[3] * TO_PERCENT     << "%\n" 
    << "Lab: "          << setw(27)                             << classAvg[0] * TO_PERCENT     << "%\n"
    << "Quiz: "         << setw(26)                             << classAvg[1] * TO_PERCENT     << "%\n"
    << "Exams: "        << setw(25)                             << classAvg[2] * TO_PERCENT     << "%\n"
    << "Final Exam: "   << setw(20)                             << classAvg[4] * TO_PERCENT     << "%\n"
    << "Total: "        << setw(25)                             << totalAvg    * TO_PERCENT     << "%\n"
    << "===============================================\n" << endl;
}

/*
 * @author: Natasha Kho
 * @author: Emily Hsu
*/
void printMenu(void){
    cout <<  "=========================================================\n"
    << "Select an option:\n"
    << "1. Generate fake data\n"
    << "2. Select which score file to use\n"
    << "3. Generate grade report\n"
    << "4. Show class average percentages\n"
    << "5. N/A\n"
    << "6. N/A \n"
    << "7. Log Out\n"
    << "8. Exit program\n"
    << "=========================================================\n";


}

/*
 * @author: Natasha Kho
 * @author: Emily Hsu
*/
void fileImport(fstream &inputFile) {
  string scoreFile; // create string var for file name
  cout << "Please Enter Score File:\n"; // prompt use to enter file name
  cin  >> scoreFile; // take filename input from user
  inputFile.open(scoreFile); // attempt to open file

  // if file did not open:
  while(inputFile.is_open() == 0) {
    inputFile.close(); // close file
    cout << "There was an error opening the file. Please enter the Score File again:\n"; // repeat prompt to open valid file
    cin  >> scoreFile; // take input from user and attempt to open file again
    inputFile.open(scoreFile);
    // if file still does not open, loop error message
  }
}


/*
 * @author: Natasha Kho
 * @author: Emily Hsu
*/
int checkFile(fstream &inputFile){
    while(!inputFile.is_open()){
        cout << "Files is not open... Please input a file to use\n";
        fileImport(inputFile);
    }
    return 1;
}
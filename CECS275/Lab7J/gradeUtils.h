/*
 * This C++ program takes an input of a file with the number of assignments per grading category,
 * the max scores of each assignment, and the student scores of each assignment, and after calculating
 * the student's grade, outputs their weighted grade for each category and final grade.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Hanna Estrada
 * @version 7.0.0
 *
*/

#include <iostream> 
#include <iomanip> 
#include <fstream>
#include <locale>
#include <string>
#include <cstdlib>


// initialize functions
using namespace std;

void userInterface(void);

std::string studentLogIn(void);

std::string resetPassword(void);

std::ifstream fileImport(void);

void gradeGen(void);

//Grade weights based on category in percents
const double labWeight = 0.15;
const double quizWeight = 0.15;
const double examWeight = 0.40;
const double projectWeight = 0.10;
const double finalWeight = 0.20;

//the thresholds 
const int aGrade = 90;
const int bGrade = 80;
const int cGrade = 70;
const int dGrade = 60;
const int fGrade = 60;

//percteage conversion
const int percentageConversion = 100;

//The string to check whether the password is correct or not 
/*const*/ string passwordCheck  = "password";
const string userCheck      = "Student";


// 275 Data: Number of Labs, Quizzes, Midterms, Projects, Final
const int numLabs275 = 20;
const int numQuizzes275 = 7;
const int numMidterms275 = 2;
const int numProjects275 = 1;
const int numFinals275 = 1;
const int maxScoreLabs275 = 5;
const int maxScoreQuizzes275 = 10;
const int maxScoreMidterms275 = 50;
const int maxScoreProjects275 = 100;
const int maxScoreFinals275 = 100;

// to account for divisor =/= remainder when using modulo
const int remainder = 1;

// to check incorrect password attempts
const int maxIncorrectPass = 3;


/*
 * This function displays a selection menu for the user, prompting them to input what they want the program to do.
 * 
 * @param user user's username as a string
 * @author Justin Narciso 
 * @author Hanna Estrada
 * version 1.0.0
*/
void displayMenu(string user) {
  // display menu to user
  cout << "\n\n\n==================================================================================================\n"
    << "Hello " << user << "! Welcome, to the Student Grade Calculator Interface.\n"
    << "Please Enter what you would like to perform:\n"  
    << "1. Random Grade Generation\n"
    << "2. Import File\n"
    << "3. Show Student Score Report\n"
    << "4. Exit and Quit\n";
}


/*
 * File Import function operates by requesting a user to input in a string scoreFile
 * this string would be the score file the user have on hand or had created
 * then using fstream fileStream it would open the file name scoreFIle
 * Once doing so fileStream is checked whether or not it is open, if not user 
 * is reprompted to enter a file until is_opens is true
 * once done so, returning fileStream to Interface where it will be called to other functions
 * 
 * @return ifstream with open file to call values within it
 * @author Justin Narciso
 * @author Hanna Estrada
 * @version 1.0.0
*/
std::ifstream fileImport(void) {
  string scoreFile; // create string var for file name
  ifstream fileStream; // create var to read fromm file
  cout << "Please Enter Score File:\n"; // prompt use to enter file name
  cin  >> scoreFile; // take filename input from user
  fileStream.open(scoreFile); // attempt to open file

  // if file did not open:
  while(fileStream.is_open() == 0) {
    fileStream.close(); // close file
    cout << "There was an error opening the file. Please enter the Score File again:\n"; // repeat prompt to open valid file
    cin  >> scoreFile; // take input from user and attempt to open file again
    fileStream.open(scoreFile);
    // if file still does not open, loop error message
  }
  return fileStream; // return valid score file
}

/*
 * This function generates a random score that is input into the file randGrades.txt. It uses for loops to input the total assignments
 * per category and and the max scores of each assignment, then uses rand() % max score to generate random scores equal to or below
 * the max score. If the score is less than half the total score, the function adds approximately half of the total score in order
 * to help generate higher grades to test. It stores the student's scores first in a temporary file, then imports the scores from
 * that file into randGrades.txt.
 *
 * @param None
 * @return None
 * @author Hanna Estrada
 * @author Justin Narciso
*/
void gradeGen(void) {
  // define variables to read/write from file, and int i for loops
  fstream temp;
  fstream scores;
  int i = 0;
  // open randGrades files for read and write
  scores.open("randGrades.txt");
  // import scores based on CECS 275 scores
  scores << numLabs275 << " " << numQuizzes275 << " " << numMidterms275 << " " << numProjects275 << " " << numFinals275 << endl;
  // use for loop to loop through total number of assignments
  for (i = 0; i < (numLabs275 + numQuizzes275 + numMidterms275 + numProjects275 + numFinals275); i++){
    if (i < numLabs275) { // check if i is within range of Lab assignments
      scores << maxScoreLabs275 << " "; // input max score of Lab assignments into randGrades.txt
    } else if (i < (numLabs275 + numQuizzes275)) { // check if i is within range of Quiz assignments
      scores << maxScoreQuizzes275 << " "; // input max score of Quiz assignments into randGrades.txt
    } else if (i < (numLabs275 + numQuizzes275 + numMidterms275)) { // check if i is within range of Midterm assignments
      scores << maxScoreMidterms275 << " "; // input max score of Midterm assignments into randGrades.txt
    } else if (i < (numLabs275 + numQuizzes275 + numMidterms275 + numProjects275)) { // check if i is within range of Project assignments
      scores << maxScoreProjects275 << " "; // input max score of Project assignments into randGrades.txt
    } else { // check for remaining assignments, mainly Finals
      scores << maxScoreFinals275 << " "; // input max score of Final assignments into randGrades.txt
    }
  }
  scores << endl; // add endline to cut off any extra scores
  scores.close(); // close random grade file to save scores
  scores.open("randGrades.txt"); // reopen file
  temp.open("temp.txt"); // need a temporary storage file because we can't read and write at the same time

  srand(time(NULL)); // set random seed to time so it always changes
  // define variables
  int maxScoreTest, studentScoreTest;
  int numLabsTest, numQuizzesTest, numMidtermsTest, numProjectsTest, numFinalsTest;
  int randScore;
  // input number of assignments for each category
  scores >> numLabsTest >> numQuizzesTest >> numMidtermsTest >> numProjectsTest >> numFinalsTest;

  // loop through all max scores and add a random student score to temporary file
  for (i = 0; i < (numLabsTest + numQuizzesTest + numMidtermsTest + numProjectsTest + numFinalsTest); i++) {
    scores >> maxScoreTest; // input max score into max score variable
    randScore = (rand() % (maxScoreTest + remainder)); // generate random score less than or equal to max score
    if (randScore <= (maxScoreTest / 2)) {
      randScore += maxScoreTest / 2; // add score boost to lessen chance of F/D grades
    }
    temp << randScore << " "; // input random score into temporary file
  }
  // close and reopen temp file to save data so we can read it
  temp.close();
  temp.open("temp.txt");

  scores << endl; // start a new line for student scores
  // read through temporary files and add to score file
  while (temp >> studentScoreTest) {
    scores << studentScoreTest << " ";
  }

  // close both score files
  temp.close();
  scores.close();
}
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

void registration(vector<string> &userDatabase, vector<string> &passwordDatabase,string &user);

void login(vector<string> userDatabase, vector<string> passwordDatabase,string &user);

void setNewPassword(vector<string> userDatabase, vector<string> passwordDatabase,string &user);

int loginMenu(vector<string> userDatabase, vector<string> passwordDatabase, string &user);

/*
 * @author Justin Narciso
 * @author Hanna Estrada
*/
void registration(vector<string> &userDatabase, vector<string> &passwordDatabase,string &user){
    string registerUsername, registerPassword;

    cout << "Enter your username: " << endl;
    cin >> registerUsername;
    for(int i=0;i<userDatabase.size();i++){
        while(registerUsername == userDatabase[i]){
            cout << "Im Sorry this username is unavaiable. Please try a different one: " << endl;
            cin >> registerUsername;
        }
    }
    user = registerUsername;
    cout << "Enter your password: " << endl;
    cin >> registerPassword;

    userDatabase.push_back(registerUsername);
    passwordDatabase.push_back(registerPassword);

    cout << "Successfully registered!" << endl;

}

/*
 * @author Justin Narciso
 * @author Hanna Estrada
*/
void login(vector<string> userDatabase, vector<string> passwordDatabase,string &user){
    int i, index, access = 0, attempt = 0;
    string inUsername, inPassword;

    cout << "Enter your username: " << endl;
    cin >> inUsername;
    do{
        for(i=0;i<userDatabase.size();i++){
            if (inUsername == userDatabase[i]){
                index = i;
                access = 1;
                break;
            }
        }if(access == 0){
            cout << "Im sorry, but this user is not within our database. Please try again: " << endl;
            cin >> inUsername;
        }
    }while(access==0);
    user = inUsername;
    access = 0;
    cout << "Enter your password: " << endl;
    cin >> inPassword;
    do{
        for(i=0;i<passwordDatabase.size();i++){
            if(inPassword == passwordDatabase[i]){
                access = 1;
                break;
            }
        }
        if(access == 0){
            cout << "The Pasword entered is incorrect. Please try again: " << endl;
            cin >> inPassword;
            attempt++;
        }if(attempt == 3){
                cout << "Im sorry, but you have been Locked Out. Please try again later..." << endl;
                break;
        }
    }while(access==0);
}

/*
 * @author Justin Narciso
 * @author Hanna Estrada
*/
void setNewPassword(vector<string> userDatabase, vector<string> passwordDatabase,string &user){
    int i, match=0, index;
    string username, newPassword;

    cout << "Enter your username: " << endl;
    cin >> username;
    do{
        for(i=0;i<userDatabase.size();i++){
            if(username == userDatabase[i]){
                match = 1;
                index = i;
                break;
            }
        } if (match == 0){
            cout << "Im Sorry this username is unavaiable. Please try a different one: " << endl;
            cin >> username;
        }
    }while(match == 0);
    cout << "Please enter your new password: " << endl;
    cin >> newPassword;
    cout << index << endl;
    passwordDatabase.at(index) = newPassword;

    for(const string& s : userDatabase){
        cout << s << " ";
    } for (const string& s : passwordDatabase){
        cout << s << " ";
    }
    user = username;
    cout << "Successfully changed password! Returning to login..." << endl;
}

/*
 * @author Justin Narciso
 * @author Hanna Estrada
*/
int loginMenu(int accountValid, vector<string> &userDatabase, vector<string> &passwordDatabase, string &user){
    int userSelect, access;
    do{
        cout << "Choose an option:\n"
        << "1. Register a new student account\n"
        << "2. Login to an existing account\n"
        << "3. Change or forgot password\n";
        cin >> userSelect;

        switch(userSelect){
        case 1: 
            registration(userDatabase, passwordDatabase, user);
            if(accountValid != 1){
                userSelect = 2;
                break;
            }
            accountValid = 1;
            break;
        
        case 2: 
            if(accountValid != 1){
                registration(userDatabase, passwordDatabase, user);
                userSelect= 2;
                break;
            } login(userDatabase, passwordDatabase, user);
            accountValid = 1;
            break;

        case 3: 
            if (accountValid != 1){
                registration(userDatabase, passwordDatabase, user);
                userSelect = 2;
                break;
            } setNewPassword(userDatabase, passwordDatabase, user);
            accountValid = 1;
            break;

        default: 
            cout << "That is not a valid selection, Please try again. " << endl;
            break;
        }
    }while(userSelect != 2);
   return 1;
}
 
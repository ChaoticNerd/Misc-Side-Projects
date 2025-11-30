#include "loginWindow.h"
//#include "mainScreen.h"
#include <iostream>
#include <fstream>
#include <string>

loginWindow::loginWindow(){
    set_title("Login Window");
    set_default_size(800, 600);
    this->loggedIn = false;
    
    //screenGrid set up to 
    screenGrid.set_halign(Gtk::Align::FILL);
    screenGrid.set_valign(Gtk::Align::FILL);

    screenGrid.set_margin(20);
    screenGrid.set_row_spacing(10);
    screenGrid.set_column_spacing(10);

    screenGrid.set_hexpand(true);
    screenGrid.set_vexpand(true);

    textBox.set_orientation(Gtk::Orientation::VERTICAL);
    textBox.set_spacing(10);
    textBox.set_margin(5);

    textBox.set_hexpand(true);
    textBox.set_vexpand(true);
    textBox.set_halign(Gtk::Align::FILL);
    textBox.set_valign(Gtk::Align::END);
    textBox.set_homogeneous(true);
    
    // username entry set up
    usernameEntry.set_placeholder_text("Username");
    usernameEntry.set_hexpand(true);
    usernameEntry.set_vexpand(true);
    usernameEntry.set_size_request(20, 20);

    // password entry set up
    passwordEntry.set_placeholder_text("Password");
    passwordEntry.set_hexpand(true);
    passwordEntry.set_vexpand(true);
    passwordEntry.set_size_request(20, 20);
    passwordEntry.set_visibility(false);

    //login button set up
    loginButton.set_label("Login");
    loginButton.set_hexpand(true);
    loginButton.set_vexpand(true);
    loginButton.set_size_request(20, 20);

    //register button set up (no major functionality yet)
    registerButton.set_label("Register");
    registerButton.set_hexpand(true);  
    registerButton.set_vexpand(true);
    registerButton.set_size_request(20, 20);

    //appends entries and buttons to the textBox so they appear in the order they are called from top to bottom
    textBox.append(usernameEntry);
    textBox.append(passwordEntry);
    textBox.append(loginButton);
    textBox.append(registerButton);

    //set up screenGrid in case for more customization 
    screenGrid.attach(textBox, 0, 300);

    set_child(screenGrid); // setting screenGrid to child so that it works

    loginButton.signal_clicked().connect(sigc::mem_fun(*this, &loginWindow::on_login_button_clicked));      // LoginButton Signal when clicked is sent out true to run the on_login_button_clicked
    registerButton.signal_clicked().connect(sigc::mem_fun(*this, &loginWindow::on_register_button_clicked));// RegisterButton Signal when clicked is sent out true to run the on_register_button_clicked
    show();
}



void loginWindow::on_login_button_clicked(void){    //Logic functionality to check if login was successful on when log in is pressed
    std::string username = usernameEntry.get_text(); //get username from entry
    std::string password = passwordEntry.get_text(); //get password from entry

    if(loginAuthentication(username, password)){
        m_signal_login_successful.emit(); // emit signal for successful login

        this -> loggedIn = (true); // set loggedIn to true
    }

}

void loginWindow::on_register_button_clicked(void){ //used to detect if register button is pressed not done just setup...
    // Placeholder for register button click handling
    std::cout << "Register button clicked!" << std::endl;
}

void loginWindow::setLoggedIn(bool status){ //set boolean to determine whether or not Login was successful
    this->loggedIn = status;
}

bool loginWindow::getLoggedIn(void)const{   //get the login bool so that it can communicated to other systems that they logged in
    return this->loggedIn;
}

sigc::signal<void()> loginWindow::signal_login_successful(void)const{   //a signal that was used to communicate that login was successful
    return m_signal_login_successful;
}



bool loginWindow::loginAuthentication(std::string username, std::string password){
    std::string file_username, file_password, databaseLine;
    std::ifstream outfile("user.txt");  //opening user database

    while (getline(outfile, databaseLine)) { // get username and password from file
        size_t delimiter_pos = databaseLine.find(' ');          // assuming username and password are separated by space
        file_username = databaseLine.substr(0, delimiter_pos);  //get username from file
        file_password = databaseLine.substr(delimiter_pos + 1); //get password from file

        std::cout << "Username: " << file_username << ", Password: " << file_password << std::endl;// debug to check file values

        if (username == file_username && password == file_password) {   //Check if username and password are correct in user database
            std::cout << "Username: " << file_username << ", Password: " << file_password << std::endl; // debug to confirm match
            std::cout << "Login successful!" << std::endl;  // debug successful login message in terminal
            outfile.close();
            return true;
        }
    }
    std::cout << "Invalid username or password." << std::endl; // debug invalid login message in terminal
    outfile.close(); //close file so that it restarts properly on next login attempt
    return false;

}
#include "loginWindow.h"
//#include "mainScreen.h"
#include <iostream>
#include <fstream>
#include <string>

loginWindow::loginWindow(){
    set_title("Login Window");
    set_default_size(800, 600);
    this->loggedIn = false;
    
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
    
    // username entry
    usernameEntry.set_placeholder_text("Username");
    usernameEntry.set_hexpand(true);
    usernameEntry.set_vexpand(true);
    usernameEntry.set_size_request(20, 20);

    // password entry
    passwordEntry.set_placeholder_text("Password");
    passwordEntry.set_hexpand(true);
    passwordEntry.set_vexpand(true);
    passwordEntry.set_size_request(20, 20);

    //login button
    loginButton.set_label("Login");
    loginButton.set_hexpand(true);
    loginButton.set_vexpand(true);
    loginButton.set_size_request(20, 20);

    //register button
    registerButton.set_label("Register");
    registerButton.set_hexpand(true);  
    registerButton.set_vexpand(true);
    registerButton.set_size_request(20, 20);

    
    textBox.append(usernameEntry);
    textBox.append(passwordEntry);
    textBox.append(loginButton);
    textBox.append(registerButton);

    screenGrid.attach(textBox, 0, 300);

    set_child(screenGrid);

    // loginButton.signal_clicked().connect([this]() {
    //     // Handle login button click event
    //     auto username = usernameEntry.get_text();
    //     auto password = passwordEntry.get_text();
    //     // Add your login logic here
    // });
    loginButton.signal_clicked().connect(sigc::mem_fun(*this, &loginWindow::on_login_button_clicked));
    registerButton.signal_clicked().connect(sigc::mem_fun(*this, &loginWindow::on_register_button_clicked));
    show();
}

void loginWindow::on_login_button_clicked(void){
    std::string file_username, file_password,line;
    std::ifstream outfile("user.txt");
    std::string username = usernameEntry.get_text(); //get username from entry
    std::string password = passwordEntry.get_text(); //get password from entry

    std::cout << "Username: " << username << ", Password: " << password << std::endl; // debug to check input values

    while (getline(outfile,line)) { // get username and password from file
        size_t delimiter_pos = line.find(' ');          // assuming username and password are separated by space
        file_username = line.substr(0, delimiter_pos);  //get username from file
        file_password = line.substr(delimiter_pos + 1); //get password from file

        std::cout << "Username: " << file_username << ", Password: " << file_password << std::endl;// debug to check file values

        if (username == file_username && password == file_password) {
            std::cout << "Username: " << file_username << ", Password: " << file_password << std::endl; // debug to confirm match
            std::cout << "Login successful!" << std::endl;  // debug successful login message in terminal

            m_signal_login_successful.emit(); // emit signal for successful login
            

            this -> loggedIn = (true); // set loggedIn to true
            //this->hide(); // close login window upon successful login   
            outfile.close(); //close file upon successful login
            return;
        }
    }
    std::cout << "Invalid username or password." << std::endl; // debug invalid login message in terminal
    outfile.close(); //close file so that it restarts properly on next login attempt
    

    // Placeholder for login button click handling
}

void loginWindow::on_register_button_clicked(void){
    // Placeholder for register button click handling
    std::cout << "Register button clicked!" << std::endl;

}

void loginWindow::setLoggedIn(bool status){
    this->loggedIn = status;
}

bool loginWindow::getLoggedIn(void)const{
    return this->loggedIn;
}

sigc::signal<void()> loginWindow::signal_login_successful(void)const{
    return m_signal_login_successful;
}
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
    std::cout << "Papyrus: SANS?! WHAT IS THAT?!\n Sans: A Hooman Pap.\n Papyrus: WELL WHO ARE THEY?!?!\n SANS: Idk, lol. Why not let them Answer? \n";
    promptRegistration();
    
}

void loginWindow::setLoggedIn(bool status){ //set boolean to determine whether or not Login was successful
    this->loggedIn = status;
}

bool loginWindow::getLoggedIn(void)const{   //get the login bool so that it can communicated to other systems that they logged in
    return this->loggedIn;
}

sigc::signal<void()>& loginWindow::signal_login_successful() { // success login
    return m_signal_login_successful;
}

bool loginWindow::loginAuthentication(std::string username, std::string password){
    std::string file_username, file_password, databaseLine;
    std::ifstream outfile("../data/user.txt");  //opening user database

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

void loginWindow::promptRegistration(void){
    auto dialog = new Gtk::Dialog("Registeration", *this);
    dialog->set_name("Reg-Box");
    dialog->set_deletable(false);
    dialog->set_modal(true);
    dialog->set_decorated(true);        // no OS title bar
    dialog->set_transient_for(*this);    // center over main window
    dialog->set_default_size(800, 580);  // tweak as you like

    Gtk::Box* content_area = dialog->get_content_area();
    content_area->set_orientation(Gtk::Orientation::VERTICAL);
    content_area->set_margin(5);
    content_area->set_halign(Gtk::Align::CENTER);
    content_area->set_valign(Gtk::Align::END);
    content_area->set_hexpand(true);
    content_area->set_vexpand(true);

    Gtk::Grid* grid = Gtk::make_managed<Gtk::Grid>();
    content_area -> append(*grid);
    grid -> set_row_spacing(5);
    grid -> set_column_spacing(5);
    grid -> set_margin(5);

    grid -> set_halign(Gtk::Align::FILL);
    grid -> set_valign(Gtk::Align::FILL);
    grid -> set_hexpand(true);
    grid -> set_vexpand(true);

    //create the buttons for Cancel and Register (placed inside the grid so they follow layout)
    Gtk::Button* cancelBtn = Gtk::make_managed<Gtk::Button>("Cancel");
    Gtk::Button* registerBtn = Gtk::make_managed<Gtk::Button>("Register");


    //Creating the 3 Entries for newUsername, newPassword, confirmPassword
    Gtk::Entry* newUser = Gtk::make_managed<Gtk::Entry>(); //Create the Entry for a newUser's username
    newUser -> set_placeholder_text("Hooman, Whats your Username?");
    newUser -> set_hexpand(true);
    newUser -> set_size_request(80, 20);

    Gtk::Entry* newPass = Gtk::make_managed<Gtk::Entry>(); // create the Entry for a new user's Password
    newPass -> set_placeholder_text("Hooman, Please enter a Password?");
    newPass -> set_hexpand(true);
    newPass -> set_size_request(80, 20);

    Gtk::Entry* confirmPass = Gtk::make_managed<Gtk::Entry>(); // create the entry to confirm the Password
    confirmPass -> set_placeholder_text("Hooman, Please re-type your Password!");
    confirmPass->set_hexpand(true);
    confirmPass -> set_size_request(80, 20);


    //Icons next to entry to show an Error
    Gtk::Label* userErrorIcon = Gtk::make_managed<Gtk::Label>("*");
    userErrorIcon -> set_hexpand(true);

    Gtk::Label* passErrorIcon = Gtk::make_managed<Gtk::Label>("*");
    passErrorIcon -> set_hexpand(true);

    Gtk::Label* passConfirmErrorIcon = Gtk::make_managed<Gtk::Label>("*");
    passConfirmErrorIcon -> set_hexpand(true);

    //Icons Above Entry to describe an error if any
    Gtk::Label* userErrorMsg = Gtk::make_managed<Gtk::Label>(" ");
    userErrorMsg -> set_hexpand(true);

    Gtk::Label* passErrorMsg = Gtk::make_managed<Gtk::Label>(" ");
    passErrorMsg -> set_hexpand(true);

    Gtk::Label* passConfirmErrorMsg = Gtk::make_managed<Gtk::Label>(" ");
    passConfirmErrorMsg -> set_hexpand(true);


    //grid pos of entries
    grid -> attach(*newUser,                1, 3, 4, 1);
    grid -> attach(*newPass,                1, 5, 4, 1);
    grid -> attach(*confirmPass,            1, 7, 4, 1);
    //grid pos of icons
    grid -> attach(*userErrorIcon,          0, 3, 1, 1);
    grid -> attach(*passErrorIcon,          0, 5, 1, 1);
    grid -> attach(*passConfirmErrorIcon,   0, 7, 1, 1);
    //Error pos of msg 
    grid -> attach(*userErrorMsg,           1, 2, 4, 1);
    grid -> attach(*passErrorMsg,           1, 4, 4, 1);
    grid -> attach(*passConfirmErrorMsg,    1, 6, 4, 1);
    // grid pos of Buttons (make buttons follow the grid layout)
    grid -> attach(*cancelBtn,              0, 9, 2, 2);
    grid -> attach(*registerBtn,            3, 9, 2, 2);
    
    // wire the grid buttons to emit dialog responses
    cancelBtn->signal_clicked().connect([dialog]() {
        dialog->response(Gtk::ResponseType::CANCEL);
    });
    registerBtn->signal_clicked().connect([dialog]() {
        dialog->response(Gtk::ResponseType::OK);
    });

    // connect the response signal and show the dialog (async)
    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &loginWindow::registrationResponse),
            dialog,                                                 // Dialog widget
            newUser,        newPass,        confirmPass,            // Entry Widgets used in response
            userErrorIcon,  passErrorIcon,  passConfirmErrorIcon,   // Labels for icons
            userErrorMsg,   passErrorMsg,   passConfirmErrorMsg     // Labels for messages
        )
    );

    dialog->show();

}

void loginWindow::registrationResponse(int response_id, Gtk::Dialog* dialog, 
    Gtk::Entry* newUser,        Gtk::Entry* newPass,        Gtk::Entry* confirmPass,
    Gtk::Label* userErrorIcon,  Gtk::Label* passErrorIcon,  Gtk::Label* passConfirmErrorIcon,
    Gtk::Label* userErrorMsg,   Gtk::Label* passErrorMsg,   Gtk::Label* passConfirmErrorMsg){
    if(response_id == Gtk::ResponseType::OK){
        std::string Username = newUser -> get_text();   //Saving Entries into string to any edits to the entries
        std::string Password = newPass -> get_text();
        std::string PasswordConfirm = confirmPass -> get_text();        
        bool errorCheck = false;

        if (!uniqueUsername(Username)){
            userErrorIcon -> set_text("X");
            userErrorMsg -> set_text("That Username is in use!");
            errorCheck = true;
            //dialog -> show();
        }   
        if(!checkPasswordSecurity(Password)){
            passErrorIcon -> set_text("X");
            passErrorMsg -> set_text("Im not sure your Password is secure!");
            errorCheck = true;
            //dialog -> show();
        }else if(!(Password == PasswordConfirm)){
            passErrorIcon -> set_text("X");
            passErrorMsg -> set_text("The Passwords Does not Match!");
            passConfirmErrorIcon -> set_text("X");
            passConfirmErrorMsg -> set_text("The Passwords Does not Match!");
            errorCheck = true;
            //dialog -> show();
        }
        if (!errorCheck){
            // std::cout << "Succssful Register" << std::endl;
            registrationSuccess(Username, Password);
            delete dialog; // clean up heap-allocated dialog
            return;
        }
    } else if (response_id == Gtk::ResponseType::CANCEL){
        delete dialog; // clean up heap-allocated dialog
        return;
    }
    //delete dialog;
}

bool loginWindow::uniqueUsername(std::string newUser){
    std::ifstream outfile("../data/user.txt");
    std::string databaseLine, file_username;

    while (std::getline(outfile, databaseLine)) { // get username and password from file
        size_t delimiter_pos = databaseLine.find(' ');          // assuming username and password are separated by space
        file_username = databaseLine.substr(0, delimiter_pos);  //get username from file
        std::cout << file_username << std::endl;
        if((newUser == file_username) && (newUser.length() == file_username.length())){    //checks if the new username matches any in the Database
            return false;
        } 
    }
    return true;
}

bool loginWindow::checkPasswordSecurity(std::string newPass){
    bool hasAlpha, hasDigit;

    if(newPass.length() < 8){
        return false;
    }
    for (char c : newPass){
        if(isalpha(c)){
            hasAlpha = true;
        } else if (isdigit(c)){
            hasDigit = true;
        }
    }
    if(hasAlpha && hasDigit){
        return true;
    }
    return false;
}

void loginWindow::registrationSuccess(std::string newUser,std::string newPass){
    std::ofstream infile("../data/user.txt", std::ios::app);

    if(infile.is_open()){
        infile << newUser << " " << newPass << std::endl;
    } else { 
        std::cerr << "Error: given file doesn't exist\n";
    }
}
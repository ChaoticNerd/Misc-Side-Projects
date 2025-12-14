#include "loginWindow.h"
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

    loginBox.set_orientation(Gtk::Orientation::VERTICAL);
    loginBox.set_spacing(10);
    loginBox.set_margin(5);

    loginBox.set_hexpand(true);
    loginBox.set_vexpand(true);
    loginBox.set_halign(Gtk::Align::FILL);
    loginBox.set_valign(Gtk::Align::END);
    loginBox.set_homogeneous(true);
    
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
    
    errorCall.set_hexpand(true);
    errorCall.set_vexpand(true);
    errorCall.set_halign(Gtk::Align::FILL);
    errorCall.set_valign(Gtk::Align::END);
    errorCall.set_label("Welcome to Grade Calc");

    //loginImage
    loginImage.set_size_request(100, 100);
    loginImage.set("assets/sprites/SaveSpriteDecor.png");

    loginImage.set_hexpand(true);
    loginImage.set_vexpand(true);
    loginImage.set_halign(Gtk::Align::CENTER);
    loginImage.set_valign(Gtk::Align::CENTER);

    //appends entries and buttons to the loginBox so they appear in the order they are called from top to bottom
    loginBox.append(loginImage);
    loginBox.append(errorCall);
    loginBox.append(usernameEntry);
    loginBox.append(passwordEntry);
    loginBox.append(loginButton);
    loginBox.append(registerButton);

    //set up screenGrid in case for more customization 
    screenGrid.attach(loginBox, 0, 300);

    set_child(screenGrid); // setting screenGrid to child so that it works

    loginButton.signal_clicked().connect(sigc::mem_fun(*this, &loginWindow::on_login_button_clicked));      // LoginButton Signal when clicked is sent out true to run the on_login_button_clicked
    registerButton.signal_clicked().connect(sigc::mem_fun(*this, &loginWindow::on_register_button_clicked));// RegisterButton Signal when clicked is sent out true to run the on_register_button_clicked
    show();
}

/**
 * Handles the Login button click: reads the username and password,
 * authenticates them against the user database, updates the UI, and
 * emits a signal if login succeeds.
 *
 * @return void
 */

void loginWindow::on_login_button_clicked(void){    //Logic functionality to check if login was successful on when log in is pressed
    std::string username = usernameEntry.get_text(); //get username from entry
    std::string password = passwordEntry.get_text(); //get password from entry

    if(loginAuthentication(username, password)){
        loginImage.set("assets/sprites/SuccessDialogFlipped.png");
        signal_login_successful.emit(username); // emit signal for successful login
        this -> loggedIn = (true); // set loggedIn to true
    } else {
        errorCall.set_label("Sorry, Username or Password is wrong");
        loginImage.set("assets/sprites/FailDialogFlipped.png");
    }

}

/**
 * Handles the Register button click by opening the registration dialog.
 *
 * @return void
 */
void loginWindow::on_register_button_clicked(void){ //used to detect if register button is pressed and opens up the prompt for registration
    promptRegistration();
    
}

/**
 * Sets the internal logged-in state of the window.
 *
 * @param status True if the user successfully logged in; false otherwise.
 * @return void
 */
void loginWindow::setLoggedIn(bool status){ //set boolean to determine whether or not Login was successful
    this->loggedIn = status;
}

/**
 * Retrieves the current login state.
 *
 * @return true if the user is logged in; false otherwise.
 */
bool loginWindow::getLoggedIn(void)const{   //get the login bool so that it can communicated to other systems that they logged in
    return this->loggedIn;
}

/**
 * Provides access to the login-success signal.
 * This signal is emitted when the user successfully logs in.
 *
 * @return A reference to the signal that observers can connect to.
 */
loginWindow::type_signal_login_success& loginWindow::signal_login_success(){
    return signal_login_successful;
}

/**
 * Authenticates the given username and password against the user database.
 *
 * @param username The username entered by the user.
 * @param password The password entered by the user.
 * @return true if the username and password match a record in data/user.txt;
 *         false otherwise.
 */
bool loginWindow::loginAuthentication(std::string username, std::string password){
    std::string file_username, file_password, databaseLine;
    std::ifstream outfile("data/user.txt");  //opening user database

    while (getline(outfile, databaseLine)) { // get username and password from file
        size_t delimiter_pos = databaseLine.find(' ');          // assuming username and password are separated by space
        file_username = databaseLine.substr(0, delimiter_pos);  //get username from file
        file_password = databaseLine.substr(delimiter_pos + 1); //get password from file

        std::cout << "Username: " << file_username << ", Password: " << file_password << std::endl;// debug to check file values

        if (username == file_username && password == file_password) {   //Check if username and password are correct in user database
            std::cout << "Username: " << file_username << ", Password: " << file_password << std::endl; // debug to confirm match
            std::cout << "Login successful!" << std::endl;  // debug successful login message in terminal
            outfile.close();
            loginImage.set("assets/sprites/SuccessDialogFlipped.png");
            return true;
        }
    }
    loginImage.set("assets/sprites/FailDialogFlipped.png");
    std::cout << "Invalid username or password." << std::endl; // debug invalid login message in terminal
    outfile.close(); //close file so that it restarts properly on next login attempt
    return false;

}

/**
 * Handles the result of the registration dialog, validating the inputs,
 * updating error labels, and writing a new user to the file if valid.
 *
 * @param response_id The dialog response (OK or CANCEL).
 * @param dialog Pointer to the registration dialog.
 * @param newUser Entry containing the desired username.
 * @param newPass Entry containing the desired password.
 * @param confirmPass Entry containing the password confirmation.
 * @param userErrorIcon Label used to display username error indicator.
 * @param passErrorIcon Label used to display password error indicator.
 * @param passConfirmErrorIcon Label used to display confirmation error indicator.
 * @param userErrorMsg Label used to display username error message.
 * @param passErrorMsg Label used to display password error message.
 * @param passConfirmErrorMsg Label used to display confirmation error message.
 * @return void
 */
void loginWindow::promptRegistration(void){
    auto dialog = new Gtk::Dialog("Registeration", *this);
    dialog->set_name("Reg Box");
    dialog->set_deletable(false);
    dialog->set_modal(true);
    dialog->set_decorated(true);        // no OS title bar
    dialog->set_transient_for(*this);    // center over main window
    dialog->set_default_size(800, 580);  // tweak as you like
    dialog->get_style_context()->add_class("Reg-Dialog");

    Gtk::Box* content_area = dialog->get_content_area();
    content_area->set_orientation(Gtk::Orientation::VERTICAL);
    content_area->set_margin(5);
    content_area->set_halign(Gtk::Align::FILL);
    content_area->set_valign(Gtk::Align::END);
    content_area->set_hexpand(true);
    content_area->set_vexpand(true);

    Gtk::Grid* grid = Gtk::make_managed<Gtk::Grid>();
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
    newUser -> set_placeholder_text("Hooman, enter Username?");
    newUser -> set_hexpand(true);
    newUser -> set_size_request(80, 20);

    Gtk::Entry* newPass = Gtk::make_managed<Gtk::Entry>(); // create the Entry for a new user's Password
    newPass -> set_placeholder_text("Hooman, enter Password?");
    newPass -> set_hexpand(true);
    newPass -> set_size_request(80, 20);

    Gtk::Entry* confirmPass = Gtk::make_managed<Gtk::Entry>(); // create the entry to confirm the Password
    confirmPass -> set_placeholder_text("Hooman, re-enter Password!");
    confirmPass->set_hexpand(true);
    confirmPass -> set_size_request(80, 20);

    Gtk::Image* registerImage = Gtk::make_managed<Gtk::Image>();
    registerImage -> set_size_request(100, 100);
    registerImage -> set("assets/sprites/SaveSpriteDecor.png");
    registerImage -> set_hexpand(true);
    registerImage -> set_vexpand(true);
    registerImage -> set_halign(Gtk::Align::CENTER);
    registerImage -> set_valign(Gtk::Align::CENTER);
    
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

    content_area -> append(*registerImage);
    content_area -> append(*grid);
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
    grid -> attach(*cancelBtn,              1, 9, 2, 2);
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
            registerImage,                                          // RegisterImage
            newUser,        newPass,        confirmPass,            // Entry Widgets used in response
            userErrorIcon,  passErrorIcon,  passConfirmErrorIcon,   // Labels for icons
            userErrorMsg,   passErrorMsg,   passConfirmErrorMsg     // Labels for messages
        )
    );

    dialog->show();

}

void loginWindow::registrationResponse(int response_id, Gtk::Dialog* dialog, 
    Gtk::Image* registerImage,
    Gtk::Entry* newUser,        Gtk::Entry* newPass,        Gtk::Entry* confirmPass,
    Gtk::Label* userErrorIcon,  Gtk::Label* passErrorIcon,  Gtk::Label* passConfirmErrorIcon,
    Gtk::Label* userErrorMsg,   Gtk::Label* passErrorMsg,   Gtk::Label* passConfirmErrorMsg){
    if(response_id == Gtk::ResponseType::OK){
        std::string Username = newUser -> get_text();   //Saving Entries into string to any edits to the entries
        std::string Password = newPass -> get_text();
        std::string PasswordConfirm = confirmPass -> get_text();        
        bool errorCheck = false;

        if (!uniqueUsername(Username)){
            registerImage -> set("assets/sprites/FailDialogFlipped.png");
            userErrorIcon -> set_text("X");
            userErrorMsg -> set_text("That Username is in use!");
            errorCheck = true;
            //dialog -> show();
        }   
        if(!checkPasswordSecurity(Password)){
            registerImage -> set("assets/sprites/FailDialogFlipped.png");
            passErrorIcon -> set_text("X");
            passErrorMsg -> set_text("Im not sure your Password is secure!");
            errorCheck = true;
            //dialog -> show();
        }else if(!(Password == PasswordConfirm)){
            registerImage -> set("assets/sprites/FailDialogFlipped.png");
            passErrorIcon -> set_text("X");
            passErrorMsg -> set_text("The Passwords Does not Match!");
            passConfirmErrorIcon -> set_text("X");
            passConfirmErrorMsg -> set_text("The Passwords Does not Match!");
            errorCheck = true;
            //dialog -> show();
        }
        if (!errorCheck){
            registerImage -> set("assets/sprites/SuccessDialogFlipped.png");
            // std::cout << "Succssful Register" << std::endl;
            registrationSuccess(Username, Password);
            delete dialog; // clean up heap-allocated dialog
            return;
        }
    } else if (response_id == Gtk::ResponseType::CANCEL){
        delete dialog; // clean up heap-allocated dialog
        return;
    }

}

bool loginWindow::uniqueUsername(std::string newUser){
    std::ifstream outfile("data/user.txt");
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
    std::ofstream infile("data/user.txt", std::ios::app);

    if(infile.is_open()){
        infile << newUser << " " << newPass << std::endl;
    } else { 
        std::cerr << "Error: given file doesn't exist\n";
    }
}
/*
 * This C++ program implements the loginWindow class, which provides a GTK-based
 * login and registration interface for the Grade Calc application.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 3.0.2
 */

#include "loginWindow.h"
#include <iostream>
#include <fstream>
#include <string>

loginWindow::loginWindow() {
    // Basic window setup
    set_title("Login Window");
    set_default_size(800, 600);
    this->loggedIn = false;

    // Layout grid configuration
    screenGrid.set_halign(Gtk::Align::FILL);
    screenGrid.set_valign(Gtk::Align::FILL);
    screenGrid.set_margin(20);
    screenGrid.set_row_spacing(10);
    screenGrid.set_column_spacing(10);
    screenGrid.set_hexpand(true);
    screenGrid.set_vexpand(true);

    // Vertical box to hold login controls
    loginBox.set_orientation(Gtk::Orientation::VERTICAL);
    loginBox.set_spacing(10);
    loginBox.set_margin(5);
    loginBox.set_hexpand(true);
    loginBox.set_vexpand(true);
    loginBox.set_halign(Gtk::Align::FILL);
    loginBox.set_valign(Gtk::Align::END);
    loginBox.set_homogeneous(true);
    
    // Username entry setup
    usernameEntry.set_placeholder_text("Username");
    usernameEntry.set_hexpand(true);
    usernameEntry.set_vexpand(true);
    usernameEntry.set_size_request(20, 20);

    // Password entry setup
    passwordEntry.set_placeholder_text("Password");
    passwordEntry.set_hexpand(true);
    passwordEntry.set_vexpand(true);
    passwordEntry.set_size_request(20, 20);
    passwordEntry.set_visibility(false);     // hide characters for password

    // Login button setup
    loginButton.set_label("Login");
    loginButton.set_hexpand(true);
    loginButton.set_vexpand(true);
    loginButton.set_size_request(20, 20);

    // Register button setup
    registerButton.set_label("Register");
    registerButton.set_hexpand(true);  
    registerButton.set_vexpand(true);
    registerButton.set_size_request(20, 20);
    
    // Status / welcome label
    errorCall.set_hexpand(true);
    errorCall.set_vexpand(true);
    errorCall.set_halign(Gtk::Align::FILL);
    errorCall.set_valign(Gtk::Align::END);
    errorCall.set_label("Welcome to Grade Calc");

    // Login image (changes based on success/failure)
    loginImage.set_size_request(100, 100);
    loginImage.set("assets/sprites/SaveSpriteDecor.png");
    loginImage.set_hexpand(true);
    loginImage.set_vexpand(true);
    loginImage.set_halign(Gtk::Align::CENTER);
    loginImage.set_valign(Gtk::Align::CENTER);

    // Pack widgets into login box (top to bottom)
    loginBox.append(loginImage);
    loginBox.append(errorCall);
    loginBox.append(usernameEntry);
    loginBox.append(passwordEntry);
    loginBox.append(loginButton);
    loginBox.append(registerButton);

    // Add login box to main grid
    screenGrid.attach(loginBox, 0, 300);

    // Set grid as the main child of the window
    set_child(screenGrid);

    // Connect button signals
    loginButton.signal_clicked().connect(
        sigc::mem_fun(*this, &loginWindow::on_login_button_clicked)
    );
    registerButton.signal_clicked().connect(
        sigc::mem_fun(*this, &loginWindow::on_register_button_clicked)
    );

    show();
}

void loginWindow::on_login_button_clicked(void) {
    // Handle Login button: read entries, authenticate, and update UI
    std::string username = usernameEntry.get_text();
    std::string password = passwordEntry.get_text();

    if (loginAuthentication(username, password)) {
        loginImage.set("assets/sprites/SuccessDialogFlipped.png");
        signal_login_successful.emit(username);  // notify listeners of success
        this->loggedIn = true;
    } else {
        errorCall.set_label("Sorry, Username or Password is wrong");
        loginImage.set("assets/sprites/FailDialogFlipped.png");
    }
}

void loginWindow::on_register_button_clicked(void) {
    // Handle Register button: open the registration dialog
    promptRegistration();
}

void loginWindow::setLoggedIn(bool status) {
    this->loggedIn = status;
}

bool loginWindow::getLoggedIn(void) const {
    return this->loggedIn;
}

loginWindow::type_signal_login_success& loginWindow::signal_login_success() {
    return signal_login_successful;
}

bool loginWindow::loginAuthentication(std::string username, std::string password) {
    std::string file_username, file_password, databaseLine;
    std::ifstream outfile("data/user.txt");  // open user database

    while (getline(outfile, databaseLine)) {
        // Split line into username and password (space-delimited)
        size_t delimiter_pos = databaseLine.find(' ');
        file_username = databaseLine.substr(0, delimiter_pos);
        file_password = databaseLine.substr(delimiter_pos + 1);

        // Check if username and password match a record
        if (username == file_username && password == file_password) {
            outfile.close();
            loginImage.set("assets/sprites/SuccessDialogFlipped.png");
            return true;
        }
    }
    // No match found
    loginImage.set("assets/sprites/FailDialogFlipped.png");
    outfile.close();
    return false;
}

void loginWindow::promptRegistration(void) {
    // Dialog created on heap; will be deleted in registrationResponse
    auto dialog = new Gtk::Dialog("Registeration", *this);
    dialog->set_name("Reg Box");
    dialog->set_deletable(false);
    dialog->set_modal(true);
    dialog->set_decorated(true);
    dialog->set_transient_for(*this);     // center over main window
    dialog->set_default_size(800, 580);
    dialog->get_style_context()->add_class("Reg-Dialog");

    Gtk::Box* content_area = dialog->get_content_area();
    content_area->set_orientation(Gtk::Orientation::VERTICAL);
    content_area->set_margin(5);
    content_area->set_halign(Gtk::Align::FILL);
    content_area->set_valign(Gtk::Align::END);
    content_area->set_hexpand(true);
    content_area->set_vexpand(true);

    Gtk::Grid* grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_row_spacing(5);
    grid->set_column_spacing(5);
    grid->set_margin(5);
    grid->set_halign(Gtk::Align::FILL);
    grid->set_valign(Gtk::Align::FILL);
    grid->set_hexpand(true);
    grid->set_vexpand(true);

    // Buttons for Cancel and Register
    Gtk::Button* cancelBtn   = Gtk::make_managed<Gtk::Button>("Cancel");
    Gtk::Button* registerBtn = Gtk::make_managed<Gtk::Button>("Register");

    // Entries for new username and password
    Gtk::Entry* newUser = Gtk::make_managed<Gtk::Entry>();
    newUser->set_placeholder_text("Hooman, enter Username?");
    newUser->set_hexpand(true);
    newUser->set_size_request(80, 20);

    Gtk::Entry* newPass = Gtk::make_managed<Gtk::Entry>();
    newPass->set_placeholder_text("Hooman, enter Password?");
    newPass->set_hexpand(true);
    newPass->set_size_request(80, 20);

    Gtk::Entry* confirmPass = Gtk::make_managed<Gtk::Entry>();
    confirmPass->set_placeholder_text("Hooman, re-enter Password!");
    confirmPass->set_hexpand(true);
    confirmPass->set_size_request(80, 20);

    // Image in the registration dialog (changes on success/failure)
    Gtk::Image* registerImage = Gtk::make_managed<Gtk::Image>();
    registerImage->set_size_request(100, 100);
    registerImage->set("assets/sprites/SaveSpriteDecor.png");
    registerImage->set_hexpand(true);
    registerImage->set_vexpand(true);
    registerImage->set_halign(Gtk::Align::CENTER);
    registerImage->set_valign(Gtk::Align::CENTER);
    
    // Icons next to entries to show an error
    Gtk::Label* userErrorIcon        = Gtk::make_managed<Gtk::Label>("*");
    Gtk::Label* passErrorIcon        = Gtk::make_managed<Gtk::Label>("*");
    Gtk::Label* passConfirmErrorIcon = Gtk::make_managed<Gtk::Label>("*");

    userErrorIcon->set_hexpand(true);
    passErrorIcon->set_hexpand(true);
    passConfirmErrorIcon->set_hexpand(true);

    // Labels above entries to describe errors (initially blank)
    Gtk::Label* userErrorMsg        = Gtk::make_managed<Gtk::Label>(" ");
    Gtk::Label* passErrorMsg        = Gtk::make_managed<Gtk::Label>(" ");
    Gtk::Label* passConfirmErrorMsg = Gtk::make_managed<Gtk::Label>(" ");

    userErrorMsg->set_hexpand(true);
    passErrorMsg->set_hexpand(true);
    passConfirmErrorMsg->set_hexpand(true);

    content_area->append(*registerImage);
    content_area->append(*grid);

    // Grid positions for entries
    grid->attach(*newUser,      1, 3, 4, 1);
    grid->attach(*newPass,      1, 5, 4, 1);
    grid->attach(*confirmPass,  1, 7, 4, 1);

    // Grid positions for icons
    grid->attach(*userErrorIcon,        0, 3, 1, 1);
    grid->attach(*passErrorIcon,        0, 5, 1, 1);
    grid->attach(*passConfirmErrorIcon, 0, 7, 1, 1);

    // Grid positions for error messages
    grid->attach(*userErrorMsg,        1, 2, 4, 1);
    grid->attach(*passErrorMsg,        1, 4, 4, 1);
    grid->attach(*passConfirmErrorMsg, 1, 6, 4, 1);

    // Grid positions for buttons
    grid->attach(*cancelBtn,   1, 9, 2, 2);
    grid->attach(*registerBtn, 3, 9, 2, 2);
    
    // Wire the grid buttons to emit dialog responses
    cancelBtn->signal_clicked().connect([dialog]() {
        dialog->response(Gtk::ResponseType::CANCEL);
    });
    registerBtn->signal_clicked().connect([dialog]() {
        dialog->response(Gtk::ResponseType::OK);
    });

    // Connect the dialog response to registrationResponse and show dialog
    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &loginWindow::registrationResponse),
            dialog,                                                 // Dialog widget
            registerImage,                                          // Dialog image
            newUser, newPass, confirmPass,                          // Entry widgets
            userErrorIcon, passErrorIcon, passConfirmErrorIcon,     // Error icons
            userErrorMsg, passErrorMsg, passConfirmErrorMsg         // Error messages
        )
    );
    dialog->show();
}

void loginWindow::registrationResponse(
    int response_id, Gtk::Dialog* dialog, 
    Gtk::Image* registerImage,
    Gtk::Entry* newUser,        Gtk::Entry* newPass,        Gtk::Entry* confirmPass,
    Gtk::Label* userErrorIcon,  Gtk::Label* passErrorIcon,  Gtk::Label* passConfirmErrorIcon,
    Gtk::Label* userErrorMsg,   Gtk::Label* passErrorMsg,   Gtk::Label* passConfirmErrorMsg
) {
    if (response_id == Gtk::ResponseType::OK) {
        // Cache entry text for validation and potential reuse
        std::string Username        = newUser->get_text();
        std::string Password        = newPass->get_text();
        std::string PasswordConfirm = confirmPass->get_text();
        bool errorCheck = false;

        // Reset messages/icons each time OK is pressed
        userErrorIcon->set_text("*");
        passErrorIcon->set_text("*");
        passConfirmErrorIcon->set_text("*");
        userErrorMsg->set_text(" ");
        passErrorMsg->set_text(" ");
        passConfirmErrorMsg->set_text(" ");

        // Validate username uniqueness
        if (!uniqueUsername(Username)) {
            registerImage->set("assets/sprites/FailDialogFlipped.png");
            userErrorIcon->set_text("X");
            userErrorMsg->set_text("That Username is in use!");
            errorCheck = true;
        }

        // Validate password strength and match
        if (!checkPasswordSecurity(Password)) {
            registerImage->set("assets/sprites/FailDialogFlipped.png");
            passErrorIcon->set_text("X");
            passErrorMsg->set_text("Im not sure your Password is secure!");
            errorCheck = true;
        } else if (Password != PasswordConfirm) {
            registerImage->set("assets/sprites/FailDialogFlipped.png");
            passErrorIcon->set_text("X");
            passErrorMsg->set_text("The Passwords Does not Match!");
            passConfirmErrorIcon->set_text("X");
            passConfirmErrorMsg->set_text("The Passwords Does not Match!");
            errorCheck = true;
        }

        // If no errors, register user and close dialog
        if (!errorCheck) {
            registerImage->set("assets/sprites/SuccessDialogFlipped.png");
            registrationSuccess(Username, Password);
            delete dialog;  // clean up heap-allocated dialog
            return;
        }
    } else if (response_id == Gtk::ResponseType::CANCEL) {
        // User cancelled the dialog
        delete dialog;
        return;
    }
}

bool loginWindow::uniqueUsername(std::string newUser) {
    std::ifstream outfile("data/user.txt");
    std::string databaseLine, file_username;

    while (std::getline(outfile, databaseLine)) {
        // Extract username portion of the line (space-delimited)
        size_t delimiter_pos = databaseLine.find(' ');
        file_username = databaseLine.substr(0, delimiter_pos);

        // Check exact match (same content and length)
        if ((newUser == file_username) && 
            (newUser.length() == file_username.length())) {
            return false;
        }
    }
    return true;
}

bool loginWindow::checkPasswordSecurity(std::string newPass) {
    bool hasAlpha = false;
    bool hasDigit = false;

    if (newPass.length() < 8) {
        return false;
    }

    for (char c : newPass) {
        if (isalpha(c)) {
            hasAlpha = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        }
    }

    return hasAlpha && hasDigit;
}

void loginWindow::registrationSuccess(std::string newUser, std::string newPass) {
    std::ofstream infile("data/user.txt", std::ios::app);

    if (infile.is_open()) {
        infile << newUser << " " << newPass << std::endl;
    } else {
        std::cerr << "Error: given file doesn't exist\n";
    }
}

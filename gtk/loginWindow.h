/*
 * This C++ program defines the loginWindow class, which provides a GTK-based
 * login and registration interface for the Grade Calc application.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 3.0.2
 */

#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <gtkmm.h>
#include <fstream>
#include <string>

/**
 * @class loginWindow
 * @brief Login and registration window for the Grade Calc application.
 *
 * This class creates a GTK window that lets a user log in with an existing
 * account or register a new one. It validates credentials against a simple
 * text file database and emits a signal on successful login.
 */
class loginWindow : public Gtk::Window {
public:
    /**
     * @brief Constructs the loginWindow and initializes all widgets.
     *
     * Sets up the layout, entry fields, buttons, and connects signals
     * for login and registration actions.
     */
    loginWindow();
    //~loginWindow();

    /**
     * @brief Sets the internal logged-in state.
     *
     * @param status True if the user is considered logged in; false otherwise.
     */
    void setLoggedIn(bool status);

    /**
     * @brief Gets the current logged-in state.
     *
     * @return true if the user is logged in; false otherwise.
     */
    bool getLoggedIn(void) const;

    // Signal type emitted when a user successfully logs in.
    using type_signal_login_success = sigc::signal<void(const Glib::ustring&)>;

    /**
     * @brief Provides access to the login-success signal.
     *
     * This signal is emitted when the login is successful so that other
     * parts of the program can react (e.g., switching to another window).
     *
     * @return A reference to the login-success signal.
     */
    type_signal_login_success& signal_login_success();

private:
    // Widgets

    // Entry boxes for username and password on the main login window.
    Gtk::Entry usernameEntry, passwordEntry;

    // Unused extra entry boxes reserved for potential expansion.
    Gtk::Entry newUserEntry, newPassEntry, newPassConfirmEntry;

    // Label used to display feedback or error messages on the main window.
    Gtk::Label errorCall;

    // Image used to visually indicate login status (default/success/fail).
    Gtk::Image loginImage;

    // Main grid used for layout.
    Gtk::Grid screenGrid;

    // Boxes used to organize login controls and (potentially) animations.
    Gtk::Box loginBox, animationBox;

    // Buttons for logging in and starting registration.
    Gtk::Button loginButton, registerButton;

    // Signal instance that is emitted on successful login.
    type_signal_login_success signal_login_successful;

    // Tracks whether the user is currently logged in.
    bool loggedIn;

    // Private Helper Functions

    /**
     * @brief Authenticates a username and password against the user database.
     *
     * Reads entries from data/user.txt and checks if the given username
     * and password match an existing record.
     *
     * @param username The username entered by the user.
     * @param password The password entered by the user.
     * @return true if the credentials match a record; false otherwise.
     */
    bool loginAuthentication(std::string username, std::string password);

    /**
     * @brief Opens the registration dialog and sets up its widgets.
     *
     * Creates the dialog for entering a new username and password, along
     * with error labels and buttons, and connects response handlers.
     */
    void promptRegistration(void);

    /**
     * @brief Handles the response from the registration dialog.
     *
     * Validates the entered username and passwords, updates error labels,
     * and writes a new user to the file if registration is successful.
     *
     * @param response_id The dialog response (e.g., OK or CANCEL).
     * @param dialog Pointer to the registration dialog.
     * @param registerImage The image which will change based on errors/success.
     * @param newUser Entry containing the desired username.
     * @param newPass Entry containing the desired password.
     * @param confirmPass Entry for re-typing the password.
     * @param userErrorIcon Label used as an icon/marker for username errors.
     * @param passErrorIcon Label used as an icon/marker for password errors.
     * @param passConfirmErrorIcon Label used as an icon/marker for confirmation errors.
     * @param userErrorMsg Label used to display the username error message.
     * @param passErrorMsg Label used to display the password error message.
     * @param passConfirmErrorMsg Label used to display the confirmation error message.
     */
    void registrationResponse(int response_id, Gtk::Dialog* dialog, 
        Gtk::Image* registerImage,
        Gtk::Entry* newUser,        Gtk::Entry* newPass,        Gtk::Entry* confirmPass,
        Gtk::Label* userErrorIcon,  Gtk::Label* passErrorIcon,  Gtk::Label* passConfirmErrorIcon,
        Gtk::Label* userErrorMsg,   Gtk::Label* passErrorMsg,   Gtk::Label* passConfirmErrorMsg);

    /**
     * @brief Checks if the given username is not already in the database.
     *
     * @param newUser The username to test for uniqueness.
     * @return true if the username is not yet in use; false otherwise.
     */
    bool uniqueUsername(std::string newUser);

    /**
     * @brief Checks whether the given password meets basic security rules.
     *
     * Requires at least 8 characters with at least one letter
     * and one digit.
     *
     * @param newPass The password to check.
     * @return true if the password is considered secure; false otherwise.
     */
    bool checkPasswordSecurity(std::string newPass);

    /**
     * @brief Appends a successfully registered user to the user database file.
     *
     * Writes the new username and password pair to data/user.txt.
     *
     * @param newUser The new username to store.
     * @param newPass The new password to store.
     */
    void registrationSuccess(std::string newUser, std::string newPass);

protected:
    /**
     * @brief Slot for when the Login button is clicked.
     *
     * Reads the input fields, attempts authentication, and updates state
     * and signals on success.
     */
    void on_login_button_clicked(void);

    /**
     * @brief Slot for when the Register button is clicked.
     *
     * Opens the registration dialog for creating a new user account.
     */
    void on_register_button_clicked(void);
};

#endif // LOGINSCREEN_H

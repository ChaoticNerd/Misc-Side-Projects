/**
 * This C++ program defines the main Gtk::Application subclass used to manage
 * the login and main windows of the grading GUI.
 *
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#ifndef APP_H
#define APP_H

#include <gtkmm.h>
#include "loginWindow.h"
#include "mainScreen.h"

/**
 * @class App
 * @brief Main application class that controls the login flow and main window.
 *
 * The App class is responsible for:
 *  - Creating and showing the login window when the application starts.
 *  - Listening for a "login success" signal from the loginWindow.
 *  - Creating and showing the mainScreen window after a successful login.
 *  - Closing and cleaning up the login window once the user logs in.
 */
class App : public Gtk::Application {
public:
    /**
     * @brief Constructs the application object with a given application ID.
     *
     * The application ID ("com.mycompany.myapp") can be changed as needed
     * to match the project or organization.
     */
    App();

protected:
    /**
     * @brief Called automatically when the application is activated.
     *
     * This creates and shows the login window as the initial UI. The main
     * window is not shown until the user successfully logs in.
     */
    void on_activate() override;

private:
    /**
     * @brief Slot called when the login window emits a successful login signal.
     *
     * @param username The username entered by the user (passed from loginWindow).
     * @param loginWin Pointer to the loginWindow that emitted the signal.
     *
     * This function creates the mainScreen window, shows it, and then closes
     * and destroys the login window.
     */
    void on_login_success(const Glib::ustring& username, loginWindow* loginWin);
};

#endif // APP_H

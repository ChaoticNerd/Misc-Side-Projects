/**
 * This C++ program implements the main Gtk::Application subclass used to
 * manage the login flow and main window of the grading GUI.
 *
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#include "app.h"

App::App() : Gtk::Application("com.mycompany.myapp"){}

void App::on_activate() {
    // Create and show ONLY the login window initially
    auto loginWin = new loginWindow();
    add_window(*loginWin);
    loginWin->present();

    // Connect the "login success" signal from the login window
    loginWin->signal_login_success().connect(
        sigc::bind(
            sigc::mem_fun(*this, &App::on_login_success),
            loginWin
        )
    );
}

void App::on_login_success(const Glib::ustring& username, loginWindow* loginWin) {
    // Create the main application window once login is successful
    auto mainWindow = new mainScreen(username);

    add_window(*mainWindow);
    mainWindow->present();

    // Close and destroy the login window now that it's no longer needed
    loginWin->hide();
    remove_window(*loginWin);
    delete loginWin;
}

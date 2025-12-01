#include "app.h"

App::App()
: Gtk::Application("com.mycompany.myapp")   // change ID as needed
{
}

void App::on_activate() {
    // Create and show ONLY the login window
    auto loginWin = new loginWindow();
    add_window(*loginWin);
    loginWin->present();

    // Connect successful login signal
    loginWin->signal_login_successful().connect(
        sigc::bind(
            sigc::mem_fun(*this, &App::on_login_success),
            loginWin
        )
    );
}

void App::on_login_success(loginWindow* loginWin) {
    // Create the main window
    auto mainWindow = new mainScreen();

    add_window(*mainWindow);
    mainWindow->present();

    // Close and destroy login window
    loginWin->hide();
    remove_window(*loginWin);
    delete loginWin;
}

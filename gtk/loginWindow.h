#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include <gtkmm.h>
#include <fstream>
#include <string>

class loginWindow : public Gtk::Window{
    public:
        loginWindow();

    private:
        Gtk::Entry usernameEntry, passwordEntry;
        Gtk::Grid screenGrid;
        Gtk::Box textBox;
        Gtk::Button loginButton;
        
        void on_login_button_clicked();
        
        
};

#endif
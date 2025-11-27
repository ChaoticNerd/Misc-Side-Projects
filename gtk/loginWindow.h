#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include <gtkmm.h>
#include <fstream>
#include <string>

class loginWindow : public Gtk::Window{
    public:
        loginWindow();
        bool getLoggedIn(void)const;

        void setLoggedIn(bool);
        
        sigc::signal<void()> signal_login_successful()const;

       
    private:
        Gtk::Entry usernameEntry, passwordEntry;
        Gtk::Grid screenGrid;
        Gtk::Box textBox;
        Gtk::Button loginButton, registerButton;
        bool loggedIn;
        sigc::signal<void()> m_signal_login_successful;

    protected:
        void on_login_button_clicked(void);
        void on_register_button_clicked(void);
        
};

#endif
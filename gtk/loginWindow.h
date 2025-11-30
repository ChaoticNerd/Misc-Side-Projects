#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include <gtkmm.h>
#include <fstream>
#include <string>

class loginWindow : public Gtk::Window{
    public:
        loginWindow();
        //~loginWindow();


        void setLoggedIn(bool); // login Success Bool setter

        bool getLoggedIn(void)const; // login Success Boolean get
        
        
        sigc::signal<void()> signal_login_successful()const; //LoginSuccess singnal to communicate login was successful

       
    private:
        Gtk::Entry usernameEntry, passwordEntry;    //Entry boxes
        Gtk::Grid screenGrid;   //Grid for layout 
        Gtk::Box textBox;       //TextBox to place in screenGrid
        Gtk::Button loginButton, registerButton; //Buttons for Login and Register
        sigc::signal<void()> m_signal_login_successful; // The Login Successful Signal
        bool loggedIn;  //Login Boolean 

        //Private Functions to do checks
        bool loginAuthentication(std::string username, std::string password);

    protected:
        void on_login_button_clicked(void);     //Login function if LoginButton was pressed
        void on_register_button_clicked(void);  //RegisterButton Function if was pressed

};

#endif
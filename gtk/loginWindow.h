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
        
        
        sigc::signal<void()>& signal_login_successful(void); //LoginSuccess singnal to communicate login was successful

       
    private:
        Gtk::Entry usernameEntry, passwordEntry;    //Entry boxes
        Gtk::Entry newUserEntry, newPassEntry, newPassConfirmEntry; 
        Gtk::Grid screenGrid;   //Grid for layout 
        Gtk::Box textBox;       //TextBox to place in screenGrid
        Gtk::Button loginButton, registerButton; //Buttons for Login and Register
        sigc::signal<void()> m_signal_login_successful; // The Login Successful Signal
        //Gtk::Dialog 
        bool loggedIn;  //Login Boolean 

        //Private Functions to do checks
        bool loginAuthentication(std::string username, std::string password);

        void promptRegistration(void); //prompt creates dialog and neccessary stuff
        //What do i need for it, 3 Entries(newUser, newPass, newPassConfirm), 6 Labels (might be 3Labels and 3 Images if have time)
        void registrationResponse(int response_id, Gtk::Dialog* dialog, 
            Gtk::Entry* newUser,        Gtk::Entry* newPass,        Gtk::Entry* confirmPass,
            Gtk::Label* userErrorIcon,  Gtk::Label* passErrorIcon,  Gtk::Label* passConfirmErrorIcon,
            Gtk::Label* userErrorMsg,   Gtk::Label* passErrorMsg,   Gtk::Label* passConfirmErrorMsg);
        bool uniqueUsername(std::string newUser);
        bool checkPasswordSecurity(std::string newPass);
        bool confirmPassword(std::string newPass, std::string confirmPass);
        void registrationSuccess(std::string newUser,std::string newPass);

    protected:
        void on_login_button_clicked(void);     //Login function if LoginButton was pressed
        void on_register_button_clicked(void);  //RegisterButton Function if was pressed

};

#endif
#include <gtkmm.h>
#include <gdk/gdkkeysyms.h> // for GDK_KEY_F11, GDK_KEY_Escape
#include "calcScores.h"
#include "mainScreen.h"
#include "loginWindow.h"

class app : public Gtk::Application{
    // public:
    //     app() : Gtk::Application("App name?"){};

    // protected:
    //     void on_activate() override{
    //         auto loginWin = new loginWindow();
    //         add_window(*loginWin);
    //         loginWin->present();

    //         // auto mainWindow = new mainScreen();
    //         // add_window(*mainWindow);
    //     }
    public:
        static Glib::RefPtr<app> create(){          //create function to simplify app creation
            return Glib::RefPtr<app>(new app());
        }

    protected:
        app() : Gtk::Application("com.example.GtkApplication"){}    //uhhhhhhhhhh i forgor what this means as an application

        void on_activate() override {   //on activate function to show login window
            show_login_window();
        }

        void show_login_window() {
            auto loginWin = new loginWindow();
            add_window(*loginWin);
            loginWin->signal_login_successful().connect(sigc::mem_fun(*this, &app::on_login_successful));
            loginWin->present();
            this->hold();
        }
        
        void on_login_successful() { // Connect to the login successful signal
            
            show_main_screen(); 
            // auto mainWindow = new mainScreen(); //create main screen window
            // add_window(*mainWindow);    //add main screen window to application
            // mainWindow->present();     //show main screen window

            // mainWindow->signal_show().connect([this]() {
            //     cout << "Main screen shown, hiding login window." << std::endl;
            //     loginWin->hide(); // Hide login window after successful login
            //     // remove_window(*loginWin);
            //     // delete loginWin; // Clean up the login window after it's hidden
            //     // loginWin = nullptr;
            // });
            loginWin->hide();
            this->release();
            //delay until main screen is shown
            // Glib::signal_timeout().connect_once([this]() {
                
            //     std::cout << "Main screen shown, hiding login window." << std::endl;
            //     loginWin->hide(); // Hide login window after successful login
            //     // remove_window(*loginWin);
            //     // delete loginWin; // Clean up the login window after it's hidden
            //     // loginWin = nullptr;
                
            // }, 999);

            // brief delay to ensure main screen shows before login window hides
            // Wait for the main screen to show
            // loginWin->hide(); // Hide login window after successful login
            // remove_window(*loginWin);

            // loginWin->signal_hide().connect([this]() {
            //     delete loginWin; // Clean up the login window after it's hidden
            //     loginWin = nullptr;
            // });
            //show_main_screen();
            
        }
        
        void show_main_screen() {   //function to show main screen after login
            auto mainWindow = new mainScreen(); //create main screen window
            add_window(*mainWindow);    //add main screen window to application
            mainWindow->present();     //show main screen window
        }
    
    private:    
        loginWindow* loginWin = nullptr;
        mainScreen* mainWindow = nullptr;
};

int main(){
    //auto launchApp = Glib::make_refptr_for_instance<app>(new app());
    auto launchApp = app::create();


   
    // mainScreen window;

    // // GTKmm 4: you must add the window to the application yourself
    // app->add_window(window);

    // // Show the window
    // window.present();

    // GTKmm 4: run() has no window parameter
    return launchApp->run();
}


// auto main = Glib::make_refptr_for_instance<app>(new app());
    // loginWin -> show();
    // launchApp -> run(loginWindow&);
    // while(loginWin.getLoggedIn() != 1){
        
    // } //BAD PRACTICE TO HAVE A BUSY WAIT LOOP LIKE THIS BUT IT WORKS FOR NOW
    // mainScreen mainWindow;
    // mainWindow -> show();
    // launchApp -> run(mainWindow);
    // cout << "Logged in, main screen shown." << std::endl;

    // auto launchApp = Gtk::Application::create("new app");
    // auto loginWin = new loginWindow();
    // add_window(*loginWin);
    // launchApp -> make_window_and_run<loginWindow>(argc, argv);

    // while(loginWin.getLoggedIn() != 1);
    // //BAD PRACTICE TO HAVE A BUSY WAIT LOOP LIKE THIS BUT IT WORKS FOR NOW
    // auto mainApp = Gtk::Application::create("main app");
    // mainApp -> make_window_and_run<loginWindow>(argc, argv);

    


    //attempt 2
    // auto app = Gtk::Application::create("new app");

    // loginWindow loginWin;
    // app->add_window(loginWin);
    // app->run(loginWin);
    // loginWin.show();

    // if (loginWin.getLoggedIn() == true){
    //     mainScreen mainWindow;
    //     app->add_window(mainWindow);
    //     mainWindow.show();
    //     loginWin.hide();
    //     app->run(mainWindow);
    // }
    //resutt in 

    //attempt 3
    //loginWindow loginWin;
    // //app->add_window(loginWin);
    // launchApp->run(*loginWin);

    // if (loginWin.getLoggedIn()){
    //     mainScreen mainWindow;
    //     //app->add_window(mainWindow);
    //     //mainWindow.show();
    //     //loginWin.hide();
    //     app->run(*mainWindow);
    // }

    // attempt 4
    // auto app = Gtk::Application::create("new app");

    // app->signal_activate().connect([app](){
    //     auto loginWin = new loginWindow();
    //     app->add_window(*loginWin);
    //     loginWin->show();
    //     if (loginWin->getLoggedIn()){
    //         auto mainWindow = new mainScreen();
    //         app->add_window(*mainWindow);
    //         mainWindow->show();
    //         loginWin->hide();
    //     }
    // });
    //return app->run();
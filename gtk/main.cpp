#include <gtkmm.h>
#include <gdk/gdkkeysyms.h> // for GDK_KEY_F11, GDK_KEY_Escape
#include "calcScores.h"
#include "mainScreen.h"


class app : public Gtk::Application{
    public:
        app() : Gtk::Application("App name?"){};

    protected:
        void on_activate() override{
            auto mainWindow = new mainScreen();
            add_window(*mainWindow);
            mainWindow -> present();

        }
};

int main(){
    auto launchApp = Glib::make_refptr_for_instance<app>(new app());

    // mainScreen window;

    // // GTKmm 4: you must add the window to the application yourself
    // app->add_window(window);

    // // Show the window
    // window.present();

    // GTKmm 4: run() has no window parameter
    return launchApp -> run();
}

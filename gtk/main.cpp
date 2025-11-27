#include <gtkmm.h>
#include <gdk/gdkkeysyms.h> // for GDK_KEY_F11, GDK_KEY_Escape
#include "mainScreen.h"

// PROGRAM HAS TO BE RUN FROM TERMINAL OF VSC
// CD INTO build AND DO ./app


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

    auto css = Gtk::CssProvider::create();
    try {
        css->load_from_path("../style.css");   
    } catch (const Glib::Error& ex) {
        std::cerr << "CSS load error: " << ex.what() << std::endl;
    }

    auto display = Gdk::Display::get_default();
    if (display) {
        Gtk::StyleContext::add_provider_for_display(
            display,
            css,
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
    }
    // GTKmm 4: run() has no window parameter
    return launchApp -> run();
}

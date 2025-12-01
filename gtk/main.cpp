#include <gtkmm.h>
#include <fontconfig/fontconfig.h>
#include <pango/pangocairo.h>
#include <gdk/gdkkeysyms.h> // for GDK_KEY_F11, GDK_KEY_Escape
#include "mainScreen.h"
#include "loginWindow.h"

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
            auto loginWin = new loginWindow();
            add_window(*loginWin);
            loginWin -> present();

        }
};

int main(){
    //Glib::ustring font_file_path = "../assets/fonts/DTM-Mono.otf";
    PangoFontMap *font_map = pango_cairo_font_map_get_default();
    if (font_map){
        if (pango_font_map_add_font_file(font_map, "../assets/fonts/DTM-Mono.otf", NULL)){
            std::cout << "font" << "../assets/fonts/DTM-Mono.otf" << "loaded Successfully." << endl;
        } else {
            std::cout << "error font not loaded" << endl;
        }
    }
    
    auto launchApp = Glib::make_refptr_for_instance<app>(new app());

    //FcConfigAppFontAddFile(FcConfigGetCurrent(), '../gtk/assets/fonts/DeterminationMonoWeb.otf');
    

    auto css = Gtk::CssProvider::create();
    try {
        css->load_from_path("../style.css");   
    } catch (const Glib::Error& ex) {
        std::cerr << "CSS load error: " << ex.what() << std::endl;
    }

    auto display = Gdk::Display::get_default();
    if (display) {
        Gtk::StyleContext::add_provider_for_display(display, css,GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }
    // GTKmm 4: run() has no window parameter
    return launchApp -> run();
}


#include <gtkmm.h>
#include <gdk/gdkkeysyms.h> // for GDK_KEY_F11, GDK_KEY_Escape
#include "calcScores.h"

class mainScreen : public Gtk::Window {
public:
    mainScreen()
    {
        set_title("GTKmm 4 Fullscreen Toggle");
        set_default_size(800, 600);

        // Simple label in the middle
        label.set_text("Press F11 to toggle fullscreen\nPress Esc to exit");
        label.set_margin(20);
        label.set_justify(Gtk::Justification::CENTER);
        set_child(label);

        // Create and attach key controller
        key_controller = Gtk::EventControllerKey::create();
        add_controller(key_controller);

        // Connect key-pressed handler
        key_controller->signal_key_pressed().connect(
            sigc::mem_fun(*this, &mainScreen::on_key_pressed),
            false
        );
    }

private:
    bool is_fullscreen_ = false;
    Gtk::Label label;
    Glib::RefPtr<Gtk::EventControllerKey> key_controller;

    bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/)
    {
        if (keyval == GDK_KEY_F11) {
            if (is_fullscreen_)
                unfullscreen();
            else
                fullscreen();

            is_fullscreen_ = !is_fullscreen_;
            return true; // event handled
        }
        else if (keyval == GDK_KEY_Escape) {
            hide();       // close window -> exits app when last window
            return true;  // event handled
        }

        return false; // let other handlers run
    }
};

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

int main()
{
    auto launchApp = Glib::make_refptr_for_instance<app>(new app());

    // mainScreen window;

    // // GTKmm 4: you must add the window to the application yourself
    // app->add_window(window);

    // // Show the window
    // window.present();

    // GTKmm 4: run() has no window parameter
    return launchApp -> run();
}

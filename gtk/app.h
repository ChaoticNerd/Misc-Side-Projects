#ifndef APP_H
#define APP_H

#include <gtkmm.h>
#include "loginWindow.h"
#include "mainScreen.h"

class App : public Gtk::Application {
public:
    App();

protected:
    void on_activate() override;

private:
    void on_login_success(loginWindow* loginWin);
};

#endif

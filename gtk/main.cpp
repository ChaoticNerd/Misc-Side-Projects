#include <gtkmm.h>
#include <fontconfig/fontconfig.h>
#include <pango/pangocairo.h>
#include <gdk/gdkkeysyms.h> // for GDK_KEY_F11, GDK_KEY_Escape
#include "mainScreen.h"
#include "loginWindow.h"
#include "app.h"

#include <filesystem>
#include <iostream>

// PROGRAM CAN NOW BE RUN BY DOUBLE-CLICKING app.exe
// We force the CWD to the EXE directory so ./data, ./assets, etc. work.

int main(int argc, char* argv[])
{
    (void)argc; // silence unused warning

    // 1) Set working directory to the folder where the EXE lives
    std::filesystem::path exeDir;

    try {
        std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
        exeDir = exePath.parent_path();
    }
    catch (const std::exception& e) {
        std::cerr << "Warning: could not resolve executable path: "
                  << e.what() << std::endl;
        exeDir = std::filesystem::current_path();
    }

    try {
        std::filesystem::current_path(exeDir);
    }
    catch (const std::exception& e) {
        std::cerr << "Warning: could not set working directory: "
                  << e.what() << std::endl;
    }

    std::cout << "Current working directory: "
              << std::filesystem::current_path() << std::endl;

    const std::filesystem::path fontPath = std::filesystem::path("assets") / "fonts" / "DTM-Mono.otf";
    const std::filesystem::path cssPath  = std::filesystem::path("style.css");

    // Sanity checks: do the files exist in this folder?
    if (!std::filesystem::exists(fontPath)) {
        std::cerr << "WARNING: Font file not found at: " << fontPath << std::endl;
    } else {
        std::cout << "Found font file: " << fontPath << std::endl;
    }

    if (!std::filesystem::exists(cssPath)) {
        std::cerr << "WARNING: CSS file not found at: " << cssPath << std::endl;
    } else {
        std::cout << "Found CSS file: " << cssPath << std::endl;
    }

    // 2) Undertale font with Pango
    {
        PangoFontMap* font_map = pango_cairo_font_map_get_default();
        if (font_map) {
            const std::string fontFile = fontPath.string();
            if (std::filesystem::exists(fontPath)) {
                if (pango_font_map_add_font_file(font_map, fontFile.c_str(), nullptr)) {
                    std::cout << "Font " << fontFile << " loaded successfully." << std::endl;
                } else {
                    std::cout << "Error: font not loaded: " << fontFile << std::endl;
                }
            } else {
                std::cout << "Skipping font load; file does not exist." << std::endl;
            }
        } else {
            std::cerr << "Warning: pango_cairo_font_map_get_default() returned null."
                      << std::endl;
        }
    }

    // 3) Create your application instance
    auto launchApp = Glib::make_refptr_for_instance<App>(new App());

    // 4) Load CSS relative to EXE
    auto css = Gtk::CssProvider::create();
    try {
        css->load_from_path(cssPath.string());
        std::cout << "CSS loaded from: " << cssPath << std::endl;
    }
    catch (const Glib::Error& ex) {
        std::cerr << "CSS load error (" << cssPath.string()
                  << "): " << ex.what() << std::endl;
    }

    auto display = Gdk::Display::get_default();
    if (display) {
        Gtk::StyleContext::add_provider_for_display(
            display,
            css,
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
    } else {
        std::cerr << "Warning: Gdk::Display::get_default() returned null."
                  << std::endl;
    }

    return launchApp->run();
}
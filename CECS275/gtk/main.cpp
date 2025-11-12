#include <gtk/gtk.h>
#include "calcScores.h"
void init(void);

// void init(void){}
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "THIS IS THE WINDOW NAME");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);

    GtkWidget *label = gtk_label_new("HELLO WORLD");
    // GtkWidget *button = g
    gtk_window_set_child(GTK_WINDOW(window), label);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    
    GtkApplication *app = gtk_application_new("com.example.gtk4hello", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

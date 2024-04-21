//
// Created by HVGia on 4/21/2024.
//
#include "login.h"

GtkWidget *nameEntry;
GtkWidget *ipEntry;
GtkWidget *portEntry;
GtkWidget *window;
SOCKET mSocket;
void callback();

using CallbackFunc = void (*)();
int argc1;
char **argv1;

void initLoginWindow(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);
    argc1 = argc;
    argv1 = argv;

    GtkBuilder *builder = gtk_builder_new();
//    gtk_builder_add_from_file(builder, "C:\\Users\\HVGia\\CLionProjects\\untitled\\client\\login.glade", NULL);

    // Load the UI description from file
    GError *error = NULL;
    if (!gtk_builder_add_from_file(builder, "C:\\Users\\HVGia\\CLionProjects\\untitled\\client\\login.glade", &error)) {
        g_warning("Error loading UI file: %s", error->message);
        g_error_free(error);
        return;
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

    // Connect signals
    gtk_builder_connect_signals(builder, NULL);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "quitbutton"));
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    nameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "nameEntry"));
    ipEntry = GTK_WIDGET(gtk_builder_get_object(builder, "ipEntry"));
    portEntry = GTK_WIDGET(gtk_builder_get_object(builder, "portEntry"));

    button = GTK_WIDGET(gtk_builder_get_object(builder, "loginbutton"));
    g_signal_connect(G_OBJECT(button), "clicked", \
            G_CALLBACK(startButtonCallback), NULL);


// Show the window
    gtk_widget_show_all(window);

    gtk_main();

}


void openChatWindow() {
    gtk_widget_destroy(window);
    initChatWindow(argc1, argv1);
}

void startButtonCallback(GtkWidget *widget, gpointer data) {
    std::cout << "He He" << std::endl;

    name = gtk_entry_get_text(GTK_ENTRY(nameEntry));
    serverIp = gtk_entry_get_text(GTK_ENTRY(ipEntry));
    port = gtk_entry_get_text(GTK_ENTRY(portEntry));

    std::cout << "name: " << name << "\tip: " << serverIp << "\tport: " << port << std::endl;

    openChatWindow();
}

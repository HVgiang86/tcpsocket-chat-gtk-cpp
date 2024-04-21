//
// Created by HVGia on 4/21/2024.
//

#include "chat.h"

GtkWidget *chatWindow;
GtkWidget *button;
GtkWidget *chatTextView1;
GtkWidget *inputTextView2;

void onMessageCallback(std::string s) {
    std::cout << " callback called" << std::endl;
    std::cout << s << std::endl;
    Message msg = deserializeMessage(s);
    totalMsg += msg.sender + ": " + msg.content + "\n\n";

    GtkTextBuffer *textBuffer;
    textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatTextView1));

    std::cout << "Total: " << totalMsg << std::endl;
    gtk_text_buffer_set_text(textBuffer, totalMsg.c_str(), -1);
}

void initChatWindow(int argc, char *argv[]) {
    connectSocket(onMessageCallback);

    // Initialize GTK
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();

    // Load the UI description from file
    GError *error = NULL;
    if (!gtk_builder_add_from_file(builder, "chatWindow.glade", &error)) {
        g_warning("Error loading UI file: %s", error->message);
        g_error_free(error);
        return;
    }

    chatWindow = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(chat_window_close), NULL);

    chatTextView1 = GTK_WIDGET(gtk_builder_get_object(builder, "textview1"));
    inputTextView2 = GTK_WIDGET(gtk_builder_get_object(builder, "textview2"));

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(sendMsg), NULL);

    gtk_widget_show_all(chatWindow);
    gtk_main();
}

std::string getMsg() {
    GtkTextIter start, end;
    GtkTextBuffer *textBuffer;
    textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(inputTextView2));

    gtk_text_buffer_get_bounds(textBuffer, &start, &end);
    const GtkTextIter s = start, e = end;
    std::string msg = gtk_text_buffer_get_text(textBuffer, &s, &e, FALSE);

    gtk_text_buffer_delete(textBuffer, &start, &end);

    return msg;
}

void sendMsg() {
    Message msg;
    msg.sender = name;
    msg.content = getMsg();

    std::string msgJson = serializeMessage(msg);

    DTCB data{};
    data.size = msgJson.length();
    data.action = 0;
    std::string dtcb = serializeControlData(data);

    std::cout << "TEST INPUT:\t" << data.action << "\t" << data.size << std::endl;
    std::cout << "TEST INPUT:\t" << msg.sender << "\t" << msg.content << std::endl;

    std::cout << "To Send:\t" << dtcb << "\tsize: " << dtcb.length() << std::endl;
    std::cout << "To Send:\t" << msgJson << "\tsize: " << msgJson.length() << std::endl;

    //send dtcb
    int bytesSentDTCB = send(sock, dtcb.c_str(), dtcb.length(), 0);
    if (bytesSentDTCB == -1) {
        std::cerr << "Error in sending message." << std::endl;
        return;
    }

    //send msg
    int bytesSentMsg = send(sock, msgJson.c_str(), msgJson.length(), 0);
    if (bytesSentMsg == -1) {
        std::cerr << "Error in sending message." << std::endl;
        return;
    }
}

void chat_window_close() {
    gtk_widget_destroy(chatWindow);
    closeConnection(sock);
}
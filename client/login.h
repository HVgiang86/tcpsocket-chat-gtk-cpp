//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_LOGIN_H
#define SOCKET_CLIENT_LOGIN_H

#include <iostream>
#include "global.h"
#include <gtk/gtk.h>
//#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <chrono>
//#include <arpa/inet.h>
#include "chat.h"
#include "SocketClient.h"

extern SOCKET mSocket;

using CallbackFunc = void (*)();

void initLoginWindow(int argc, char *argv[]);

void startButtonCallback(GtkWidget *widget, gpointer data);

void openChatWindow();

void connectSocket();


#endif //SOCKET_CLIENT_LOGIN_H

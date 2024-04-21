//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_CHAT_H
#define SOCKET_CLIENT_CHAT_H

#include <iostream>
#include "global.h"
#include <gtk/gtk.h>
//#include <sys/socket.h>
#include <sys/types.h>
#include "SocketClient.h"
#include <thread>
#include <chrono>
#include <winsock2.h>
#include <string>
#include "../Serializer.h"

void initChatWindow(int argc, char *argv[]);
void sendMsg();
void chat_window_close();
std::string getMsg();


#endif //SOCKET_CLIENT_CHAT_H

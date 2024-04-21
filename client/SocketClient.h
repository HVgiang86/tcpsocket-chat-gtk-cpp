//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_SOCKETCLIENT_H
#define SOCKET_CLIENT_SOCKETCLIENT_H

#include "global.h"
#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>
#include "../Serializer.h"
#include "../FileHelper.h"
#include "login.h"

#pragma comment(lib, "ws2_32.lib")

using CallbackFunc1 = void (*)(std::string);

void receiveMessages(SOCKET sock, CallbackFunc1 callback);

void socketClientConnect(CallbackFunc1 callback);

void closeConnection(SOCKET sock);
void connectSocket(CallbackFunc1 callback);


#endif //SOCKET_CLIENT_SOCKETCLIENT_H

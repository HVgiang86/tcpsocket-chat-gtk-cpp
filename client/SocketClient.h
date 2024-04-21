//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_SOCKETCLIENT_H
#define SOCKET_CLIENT_SOCKETCLIENT_H

#include "global.h"
#include <iostream>
#include <string>
#include <thread>
#include "../Serializer.h"
#include "../FileHelper.h"
#include "login.h"
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using CallbackFunc1 = void (*)(std::string);

void receiveMessages(int sock, CallbackFunc1 callback);

void socketClientConnect(const std::string& serverIp, const std::string& port, CallbackFunc1 callback);

void closeConnection(int sock);

void connectSocket(CallbackFunc1 callback);


#endif //SOCKET_CLIENT_SOCKETCLIENT_H

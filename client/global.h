//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_GLOBAL_H
#define SOCKET_CLIENT_GLOBAL_H

#include <iostream>
#include <string>
#include <sys/socket.h>

extern std::string name;
extern std::string serverIp;
extern std::string port;
extern int sock; // Using int instead of SOCKET for Linux
extern std::string totalMsg;

#endif //SOCKET_CLIENT_GLOBAL_H

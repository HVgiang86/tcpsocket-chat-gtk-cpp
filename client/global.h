//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_GLOBAL_H
#define SOCKET_CLIENT_GLOBAL_H

#include <iostream>
#include <winsock2.h>

extern std::string name;
extern std::string serverIp;
extern std::string port;
extern SOCKET sock;
extern std::string totalMsg;

#endif //SOCKET_CLIENT_GLOBAL_H

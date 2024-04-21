//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_SOCKETSERVER_H
#define SOCKET_CLIENT_SOCKETSERVER_H

#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <stdexcept>
#include <string>
#include <cstring>
#include <algorithm>
#include <mutex>
#include "Serializer.h"

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

class SocketServer {
private:
    WSADATA wsaData;
    SOCKET serverSocket;
    struct sockaddr_in server;
    std::vector<std::thread> clientThreads;
    std::vector<SOCKET> clients;
    std::mutex clientsMutex;

public:
    explicit SocketServer(int port);
    ~SocketServer();
    void clientHandler(SOCKET clientSocket);
//    [[nodiscard]] Data receiveData() const;
//    void sendData(const Data &data) const;
    void run();

};


#endif //SOCKET_CLIENT_SOCKETSERVER_H

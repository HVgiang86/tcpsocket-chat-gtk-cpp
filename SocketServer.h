//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_SOCKETSERVER_H
#define SOCKET_CLIENT_SOCKETSERVER_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <stdexcept>
#include <pthread.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <mutex>
#include "Serializer.h"
#include <arpa/inet.h>
#include <thread>

class SocketServer {
private:
    int serverSocket;
    struct sockaddr_in server;
    std::vector<std::thread> clientThreads;
    std::vector<int> clients;
    std::mutex clientsMutex;

public:
    explicit SocketServer(int port);
    ~SocketServer();
    void clientHandler(int clientSocket);
    void run();
};


#endif //SOCKET_CLIENT_SOCKETSERVER_H

//
// Created by HVGia on 4/21/2024.
//
#include "SocketClient.h"


void receiveMessages(int sock, CallbackFunc1 callback) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "Received: " << buffer << std::endl;
            callback(buffer);
        }
    }
}

void connectSocket(const std::string& serverIp, const std::string& port, CallbackFunc1 callback) {
    std::thread(socketClientConnect, serverIp, port, callback).detach();
}

void socketClientConnect(const std::string& serverIp, const std::string& port, CallbackFunc1 callback) {
    int mSock = socket(AF_INET, SOCK_STREAM, 0);
    if (mSock == -1) {
        std::cerr << "Socket creation failed." << std::endl;
        return;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(std::stoi(port));
    server.sin_addr.s_addr = inet_addr(serverIp.c_str());

    if (connect(mSock, reinterpret_cast<struct sockaddr *>(&server), sizeof(server)) == -1) {
        std::cerr << "Connection failed." << std::endl;
        close(mSock);
        return;
    }

    std::cout << "Connected to server. Start typing messages." << std::endl;

    // Start a thread to receive messages from the server
    std::thread receiverThread(receiveMessages, mSock, callback);
    receiverThread.detach();

    // Keep the main thread alive
    while(true);
}

void closeConnection(int sock) {
    // Cleanup
    close(sock);
}
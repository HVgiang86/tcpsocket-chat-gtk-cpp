//
// Created by HVGia on 4/21/2024.
//
#include "SocketClient.h"


void receiveMessages(SOCKET sock, CallbackFunc1 callback) {
    char buffer[1024];
    while (true) {
        ZeroMemory(buffer, sizeof(buffer));
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "Received: " << buffer << std::endl;
        }

        std::cout << buffer << std::endl;
        callback(buffer);
    }
}

void connectSocket(CallbackFunc1 callback) {
    std::thread(socketClientConnect, callback).detach();
}

void socketClientConnect(CallbackFunc1 callback) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    SOCKET mSock = socket(AF_INET, SOCK_STREAM, 0);
    if (mSock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed." << std::endl;
        WSACleanup();
        return;
    }

    sock = mSock;

    std::string ipAddress = serverIp; // IP address of the server
    int serverPort = std::stoi(port); // Listening port # on the server

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(serverPort);
    server.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (connect(mSock, reinterpret_cast<sockaddr *>(&server), sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Connection failed." << std::endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    std::cout << "Connected to server. Start typing messages." << std::endl;

    // Start a thread to receive messages from the server
    std::thread receiverThread(receiveMessages, mSock, callback);

    while(true);
}

void closeConnection(SOCKET sock) {

    // Cleanup
    closesocket(sock);
    WSACleanup();
}
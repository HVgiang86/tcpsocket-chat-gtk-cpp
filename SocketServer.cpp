//
// Created by HVGia on 4/21/2024.
//

#include "SocketServer.h"


SocketServer::SocketServer(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw std::runtime_error("Socket creation failed");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *) &server, sizeof(server)) == -1) {
        close(serverSocket);
        throw std::runtime_error("Bind failed");
    }

    if (listen(serverSocket, 5) == -1) {
        close(serverSocket);
        throw std::runtime_error("Listen failed");
    }
}

SocketServer::~SocketServer() {
    close(serverSocket);
}

void SocketServer::clientHandler(int clientSocket) {
    try {
        char dtcbBuffer[255];
        const int MAX_DATA_BUFFER_SIZE = 1000;
        std::string receivedDTCB;
        DTCB dtcb{0,0};
        std::string msgJson;
        Message msg;
        int receivedSize = 0;
        char buffer[MAX_DATA_BUFFER_SIZE];

        std::cout << "DTCB Buffer size: " << sizeof(dtcbBuffer) << std::endl;
        std::cout << "Client connected. Handling in new thread." << std::endl;

        bool hasDTCB = false;
        bool endReceive = false;

        while (true) {
            if (!hasDTCB) {
                int recvSize = recv(clientSocket, dtcbBuffer, sizeof(dtcbBuffer), 0);
                if (recvSize == -1) {
                    throw std::runtime_error("Receive failed");
                } else if (recvSize == 0) {
                    std::cout << "Client disconnected." << std::endl;
                    break;
                }

                std::cout << "Received DTCB size: " << recvSize << std::endl;
                std::cout << dtcbBuffer << std::endl;
                receivedDTCB.append(dtcbBuffer, recvSize);
                hasDTCB = true;

                dtcb = deserializeControlData(receivedDTCB);
                std::cerr << "Received: Action: " << dtcb.action << "\nData Size: " << dtcb.size << std::endl;
                continue;
            }

            if (hasDTCB && !endReceive) {
                std::cout << "DTCB size: " << dtcb.size << std::endl;
                std::cout << "DTCB action: " << dtcb.action << std::endl;

                if (dtcb.action == 0) {
                    ZeroMemory(buffer, sizeof(buffer));
                    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
                    if (recvSize == -1) {
                        throw std::runtime_error("Receive failed");
                    } else if (recvSize == 0) {
                        std::cout << "Client disconnected." << std::endl;
                        break;
                    }

                    std::cout << "Received data size: " << recvSize << std::endl;
                    msgJson.append(buffer, recvSize);

                    receivedSize += recvSize;

                    if (receivedSize >= dtcb.size) {
                        msg = deserializeMessage(msgJson);
                        std::cout << "Received a message: " << msg.sender << "\tcontent: " << msg.content << std::endl;
                        endReceive = true;
                    }
                } else {
                    ZeroMemory(buffer, sizeof(buffer));
                    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
                    if (recvSize == -1) {
                        throw std::runtime_error("Receive failed");
                    } else if (recvSize == 0) {
                        std::cout << "Client disconnected." << std::endl;
                        break;
                    }

                    std::cout << "Received data size: " << recvSize << std::endl;
                    msgJson.append(buffer, recvSize);

                    receivedSize += recvSize;

                    if (receivedSize >= dtcb.size) {
                        msg = deserializeMessage(msgJson);
                        std::cout << "Received a message: " << msg.sender << "\tcontent: " << msg.content << std::endl;
                        endReceive = true;
                    }
                }
            }

            if (hasDTCB && endReceive) {
                if (dtcb.action == 0) {
                    std::cout << "Message back" <<std::endl;
                    send(clientSocket, msgJson.c_str(), msgJson.length(), 0);
                }

                receivedDTCB.clear();
                memset(dtcbBuffer, 0, sizeof(dtcbBuffer));
                msgJson.clear();
                memset(buffer, 0, sizeof(buffer));

                msg.sender = "";
                msg.content = "";

                dtcb.size = 0;
                dtcb.action = 0;
                hasDTCB = false;
                endReceive = false;
            }
        }
        std::cout << "All Client End!" << std::endl;

        close(clientSocket);
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());

    } catch (const std::exception &e) {
        std::cerr << "Error (Thread): " << e.what() << std::endl;
    }
}

void SocketServer::run() {
    std::cout << "Server started. Waiting for clients..." << std::endl;
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &clientAddrLen);
        if (clientSocket != -1) {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
            std::thread(&SocketServer::clientHandler, this, clientSocket).detach();
        } else {
            std::cerr << "Failed to accept client." << std::endl;
        }
    }
}

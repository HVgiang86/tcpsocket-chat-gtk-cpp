//
// Created by HVGia on 4/21/2024.
//

#include "SocketServer.h"


SocketServer::SocketServer(int port) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup Failed");
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Socket creation failed");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        throw std::runtime_error("Bind failed");
    }

    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        closesocket(serverSocket);
        WSACleanup();
        throw std::runtime_error("Listen failed");
    }
}

SocketServer::~SocketServer() {
    closesocket(serverSocket);
    WSACleanup();
}


void SocketServer::clientHandler(SOCKET clientSocket) {
    try {

        char dtcbBuffer[255];
        const int MAX_DATA_BUFFER_SIZE = 1000;
        std::string receivedDTCB;
        DTCB dtcb{0,0};
        std::string msgJson;
        Message msg;
        int receivedSize;
        char buffer[MAX_DATA_BUFFER_SIZE];

        std::cout << "DTCB Buffer size: " << sizeof(dtcbBuffer) << std::endl;
        std::cout << "Client connected. Handling in new thread." << std::endl;

        bool hasDTCB = false;
        bool endReceive = false;

        while (true) {
//            //print flag
//            std::cout << "Flags: " << std::endl;
//            std::cout << "hasDTCB: " << hasDTCB << std::endl;
//            std::cout << "end receive: " << endReceive << std::endl;

            //No DTCB flag => receive DTCB
            //Receive DTCB
            if (!hasDTCB) {
                int recvSize = recv(clientSocket, dtcbBuffer, sizeof(dtcbBuffer), 0);
                if (recvSize == SOCKET_ERROR) {
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

            //Has DTCB flag && no End recive flag => receive real data
            if (hasDTCB && !endReceive) {
                std::cout << "DTCB size: " << dtcb.size << std::endl;
                std::cout << "DTCB action: " << dtcb.action << std::endl;

                if (dtcb.action == 0) {
                    //receive msg
                    ZeroMemory(buffer, sizeof(buffer));
                    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
                    if (recvSize == SOCKET_ERROR) {
                        throw std::runtime_error("Receive failed");
                    } else if (recvSize == 0) {
                        std::cout << "Client disconnected." << std::endl;
                        break;
                    }

                    std::cout << "Received data size: " << recvSize << std::endl;
                    msgJson.append(buffer, recvSize);

                    receivedSize += recvSize;

                    //If received enough
                    if (receivedSize >= dtcb.size) {
                        msg = deserializeMessage(msgJson);
                        std::cout << "Received a message: " << msg.sender << "\tcontent: " << msg.content << std::endl;
                        endReceive = TRUE;
                    }

                } else {
                    //Receive file

                    ZeroMemory(buffer, sizeof(buffer));
                    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
                    if (recvSize == SOCKET_ERROR) {
                        throw std::runtime_error("Receive failed");
                    } else if (recvSize == 0) {
                        std::cout << "Client disconnected." << std::endl;
                        break;
                    }

                    std::cout << "Received data size: " << recvSize << std::endl;
                    msgJson.append(buffer, recvSize);

                    receivedSize += recvSize;

                    //If received enough
                    if (receivedSize >= dtcb.size) {
                        msg = deserializeMessage(msgJson);
                        std::cout << "Received a message: " << msg.sender << "\tcontent: " << msg.content << std::endl;
                        endReceive = TRUE;
                    }
                }
            }

            //has dtcb and end of receiving data => reset flag and buffer
            if (hasDTCB && endReceive) {
//                Broadcast the received message back to all clients
                if (dtcb.action == 0) {
                    std::cout << "Message back" <<std::endl;
                    for (SOCKET sock : clients) {
                        send(sock, msgJson.c_str(), msgJson.length(), 0);
                    }
                }

                receivedDTCB.clear();
                ZeroMemory(dtcbBuffer, sizeof(dtcbBuffer));
                msgJson.clear();
                ZeroMemory(buffer, sizeof(buffer));

                msg.sender = "";
                msg.content = "";

                dtcb.size = 0;
                dtcb.action = 0;
                hasDTCB = false;
                endReceive = false;

            }

            std::lock_guard<std::mutex> lock(clientsMutex);

        }

        std::cout << "All Client End!" << std::endl;

        closesocket(clientSocket);
        clientsMutex.lock();
        clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
        clientsMutex.unlock();

    } catch (const std::exception &e) {
        std::cerr << "Error (Thread): " << e.what() << std::endl;
    }


}

void SocketServer::run() {
    std::cout << "Server started. Waiting for clients..." << std::endl;
    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket != INVALID_SOCKET) {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
            std::thread(&SocketServer::clientHandler, this, clientSocket).detach();
        } else {
            std::cerr << "Failed to accept client." << std::endl;
        }
    }
}


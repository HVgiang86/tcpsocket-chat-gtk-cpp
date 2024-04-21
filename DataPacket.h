//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_DATAPACKET_H
#define SOCKET_CLIENT_DATAPACKET_H

#endif //SOCKET_CLIENT_DATAPACKET_H
#include "string"

/**
 * action table:
 * 0: send message
 * 1: send raw buffer (file)
 */


typedef struct DataTransferControlBlock {
    int action;
    int size;
} DTCB;

typedef struct FileInfo{
    std::string name;
    std::string ext;
} FileInfo;


typedef struct Message {
    std::string sender;
    std::string content;
} Message;

//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_SERIALIZER_H
#define SOCKET_CLIENT_SERIALIZER_H

#include "DataPacket.h"
#include <cstring> // for memcpy
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <iostream>

/**
 * @author Giang Hoang
 * @param data Data Transfer Control Block instance
 * @return json String
 */
std::string serializeControlData(const DTCB &data);

/**
 * @author Giang Hoang
 * @param data json String
 * @return Data Transfer Control Block instance
 */
DTCB deserializeControlData(const std::string& data);

/**
 * @author Giang Hoang
 * @param msg Message instance
 * @return json String
 */
std::string serializeMessage(const Message& msg);

/**
 * @author Giang Hoang
 * @param data json String
 * @return Message instance
 */
Message deserializeMessage(const std::string& data);


/**
 * @author Giang Hoang
 * @param msg Message instance
 * @return json String
 */
std::string serializeFileInfo(const FileInfo& fi);

/**
 * @author Giang Hoang
 * @param data json String
 * @return Message instance
 */
FileInfo deserializeFileInfo(const std::string& data);


#endif //SOCKET_CLIENT_SERIALIZER_H

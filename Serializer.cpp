//
// Created by HVGia on 4/21/2024.
//

#include "Serializer.h"

std::string serializeControlData(const DTCB &data) {
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator();

    jsonDoc.AddMember("action", data.action, allocator);
    jsonDoc.AddMember("size", data.size, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    std::string jsonStr = buffer.GetString();
    return jsonStr;
}

DTCB deserializeControlData(const std::string &data) {
    // Parse JSON
    rapidjson::Document jsonDoc;
    jsonDoc.Parse(data.c_str());
    DTCB dataPacket;

    if (jsonDoc.HasParseError()) {
        std::cerr << "Error parsing JSON." << std::endl;
    } else {
        // Process the parsed JSON document
        std::cout << "Received JSON:" << std::endl;
        std::cout << data << std::endl;
        if (!jsonDoc.HasMember("action")) {
            std::cerr << "no member action found" << std::endl;
        }

        dataPacket.action = jsonDoc["action"].GetInt();

        if (!jsonDoc.HasMember("size")) {
            std::cerr << "no member size found" << std::endl;
        }

        dataPacket.size = jsonDoc["size"].GetInt();

        std::cerr << dataPacket.size << "\t" << dataPacket.action << std::endl;
    }

    return dataPacket;
}

std::string serializeMessage(const Message &msg) {
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator();

    rapidjson::Value senderV(msg.sender.c_str(), msg.sender.length());
    rapidjson::Value contentV(msg.content.c_str(), msg.content.length());


    jsonDoc.AddMember("sender", senderV, allocator);
    jsonDoc.AddMember("content", contentV, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    std::string jsonStr = buffer.GetString();
    return jsonStr;
}

Message deserializeMessage(const std::string &data) {
    // Parse JSON
    rapidjson::Document jsonDoc;
    jsonDoc.Parse(data.c_str());
    Message msg;

    if (jsonDoc.HasParseError()) {
        std::cerr << "Error parsing JSON." << std::endl;
    } else {
        // Process the parsed JSON document
        std::cout << "Received JSON:" << std::endl;
        std::cout << data << std::endl;
        if (!jsonDoc.HasMember("sender")) {
            std::cerr << "no member sender found" << std::endl;
        }

        msg.sender = jsonDoc["sender"].GetString();

        if (!jsonDoc.HasMember("content")) {
            std::cerr << "no member content found" << std::endl;
        }

        msg.content = jsonDoc["content"].GetString();
    }

    return msg;
}

std::string serializeFileInfo(const FileInfo &fi) {
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator();

    rapidjson::Value nameV(fi.name.c_str(), fi.name.length());
    rapidjson::Value extV(fi.ext.c_str(), fi.ext.length());


    jsonDoc.AddMember("name", nameV, allocator);
    jsonDoc.AddMember("ext", extV, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    std::string jsonStr = buffer.GetString();
    return jsonStr;
}

FileInfo deserializeFileInfo(const std::string &data) {
// Parse JSON
    rapidjson::Document jsonDoc;
    jsonDoc.Parse(data.c_str());
    FileInfo fi;

    if (jsonDoc.HasParseError()) {
        std::cerr << "Error parsing JSON." << std::endl;
    } else {
        // Process the parsed JSON document
        std::cout << "Received JSON:" << std::endl;
        std::cout << data << std::endl;
        if (!jsonDoc.HasMember("name")) {
            std::cerr << "no member name found" << std::endl;
        }

        fi.name = jsonDoc["name"].GetString();

        if (!jsonDoc.HasMember("ext")) {
            std::cerr << "no member ext found" << std::endl;
        }

        fi.ext = jsonDoc["ext"].GetString();
    }

    return fi;
}
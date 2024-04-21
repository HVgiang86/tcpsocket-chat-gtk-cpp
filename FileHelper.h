//
// Created by HVGia on 4/21/2024.
//

#ifndef SOCKET_CLIENT_FILEHELPER_H
#define SOCKET_CLIENT_FILEHELPER_H
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<char> readFileIntoByteArray(const std::string& filename);

bool writeByteArrayToFile(const std::vector<char>& byteArray, const std::string& filename);

#endif //SOCKET_CLIENT_FILEHELPER_H

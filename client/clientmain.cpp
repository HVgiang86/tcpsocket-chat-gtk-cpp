//
// Created by HVGia on 4/21/2024.
//
#include <iostream>
#include <winsock2.h>
#include <string>
#include <thread>
#include "../Serializer.h"
#include "../FileHelper.h"
#include "login.h"

#pragma comment(lib, "ws2_32.lib")


int main(int argc, char* argv[]) {
    initLoginWindow(argc, argv);

    return 0;
}

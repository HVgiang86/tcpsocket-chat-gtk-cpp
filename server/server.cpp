//
// Created by HVGia on 4/21/2024.
//

#include "../SocketServer.h"

int main() {
    try {
        SocketServer server(55555);
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
//
// Created by HVGia on 4/21/2024.
//
#include "FileHelper.h"

// Function to read file into byte array
std::vector<char> readFileIntoByteArray(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // Open the file in binary mode
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return {};
    }

    // Determine the file size
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Create a vector to hold the byte array
    std::vector<char> byteArray(fileSize);

    // Read the file into the byte array
    if (!file.read(byteArray.data(), fileSize)) {
        std::cerr << "Failed to read the file." << std::endl;
        file.close();
        return {};
    }

    // Close the file
    file.close();

    return byteArray;
}

// Function to write from byte array to file
bool writeByteArrayToFile(const std::vector<char>& byteArray, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary); // Open the file in binary mode
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }

    // Write the byte array to the file
    file.write(byteArray.data(), byteArray.size());

    // Check for any write errors
    if (!file) {
        std::cerr << "Failed to write to the file." << std::endl;
        file.close();
        return false;
    }

    // Close the file
    file.close();

    return true;
}
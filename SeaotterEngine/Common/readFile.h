#pragma once

#include <vector>
#include <fstream>

inline std::vector<uint8_t> ReadCSO(const wchar_t* filename) {

    std::ifstream shaderFile(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if(!shaderFile)
        throw std::runtime_error("ReadCSO");

    const std::streampos len = shaderFile.tellg(); // get the length of file in bytes

    std::vector<uint8_t> blob;
    blob.resize(size_t(len));

    shaderFile.seekg(0, std::ios::beg); // change the get pointer to begin
    shaderFile.read(reinterpret_cast<char*>(blob.data()), len);
    shaderFile.close();

    return blob;
}
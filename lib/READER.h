#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

char* getFile(const char* FileName) {
    std::ifstream file(FileName, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro: " << FileName << std::endl;
        char* empty = new char[1];
        empty[0] = '\0';
        return empty; 
    }

    std::streamsize size = file.tellg();
    if (size == 0) {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }
    
    file.seekg(0, std::ios::beg);

    char* buffer = new char[size + 1];

    if (!file.read(buffer, size)) {
        std::cerr << "Erro ao ler o ficheiro: " << FileName << std::endl;
        delete[] buffer;
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }

    buffer[size] = '\0';

    file.close();
    return buffer;
}

#endif
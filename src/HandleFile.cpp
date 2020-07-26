#include "HandleFile.h"
#include <iostream>
#include <string>
#include <fstream>

HandleFile::HandleFile(const std::string& filepath) : filepath(filepath){}
HandleFile::HandleFile() {}

bool HandleFile::write(const std::string& line) {

    std::ofstream stream(filepath, std::ios::app);
    if (stream.is_open()) {
        stream  << line;
        stream.close();
        return true;
    }
    else {
        system("mkdir pass");
        stream << "";
        stream.close();
        return false;
    }
}

std::string HandleFile::read() {
    std::ifstream stream(filepath);
    std::string line;
    std::string stringReturn;
    while (getline(stream, line)) {
        stringReturn += line + '\n';
    }
    return stringReturn;
}
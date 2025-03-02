#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/managers/file.hpp"

File::File(std::string _source) : file(_source, std::ios::in | std::ios::out) {
    File::source = _source;
    File::file.open(File::source, std::ios::in);

    if (!File::file.is_open()) {
        File::file.open(File::source, std::ios::out);
    }
}

File::~File() {
    if (File::file.is_open()) {
        File::saveArchive();
        File::file.close();
    }
}

void File::readArchive() {
    if (File::file.is_open()) {
        file.clear();
        file.seekg(0, std::ios::beg);
        std::string buffer_line;
        while (std::getline(File::file, buffer_line)) {
            File::lines.push_back(buffer_line);
        }
    }
}

void File::saveArchive() {
    if (File::file.is_open()) {
        file.clear();
        file.seekp(0, std::ios::beg);

        for (int i = 0; i < File::lines.size(); i++) {
            File::file << File::lines[i];
            if (i != File::lines.size() -1) {
                File::file << '\n';
            }
        }
    }
}

void File::clearLines() {
    File::lines.clear();
}

void File::setLine(std::string _line) {
    File::lines.push_back(_line);
}

void File::removeLine(int _index) {
    if (_index < File::lines.size()) {
        File::lines.erase(File::lines.begin() + _index);
    }
}

std::string File::getLine(int _index) {
    if (File::lines.size() > _index) {
        return File::lines[_index];
    }
    return " ";
}

int File::getLinesCount() {
    return File::lines.size();
}
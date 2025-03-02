#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <fstream>
#include <vector>

class File {
    private:
    std::fstream file;
    std::vector<std::string> lines;
    std::string source;

    public:
    File(std::string source);
    ~File();
    void readArchive();
    void saveArchive();
    void clearLines();

    void setLine(std::string _line);
    void removeLine(int _index);

    std::string getLine(int _index);
    int getLinesCount();
};

#endif
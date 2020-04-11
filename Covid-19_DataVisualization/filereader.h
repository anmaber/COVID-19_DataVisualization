#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <unordered_map>

using DataTable = std::vector<std::vector<std::string>>;

class FileReader
{
    std::string fileName;
    DataTable values;

public:
    FileReader(const std::string& fileToReadName);
    void read();
};

#endif // FILEREADER_H

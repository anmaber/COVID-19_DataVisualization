#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <unordered_map>

using DataTable = std::vector<std::vector<std::string>>;
using CountryIndexMap = std::unordered_map<std::string, int>;

class FileReader
{
    std::string fileName;
    DataTable values;
    CountryIndexMap countryIndex;

public:
    FileReader(const std::string& fileToReadName);
    void read();
    void getCountryIndices();
};

#endif // FILEREADER_H

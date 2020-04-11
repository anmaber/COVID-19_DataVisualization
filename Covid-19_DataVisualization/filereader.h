#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <unordered_map>

struct Geolocation
{
    float latitude;
    float longtitude;
};

using DataTable = std::vector<std::vector<std::string>>;
using CountryIndexMap = std::unordered_map<std::string, int>;
using CountryGeolocationMap = std::unordered_map<std::string,Geolocation>;

class FileReader
{
    std::string fileName;
    DataTable values;
    CountryIndexMap countryIndex;
    CountryGeolocationMap countryGeolocation;

public:
    FileReader(const std::string& fileToReadName);
    void read();
    void getCountryIndices();
    void getCountryGeolocation();
};

#endif // FILEREADER_H

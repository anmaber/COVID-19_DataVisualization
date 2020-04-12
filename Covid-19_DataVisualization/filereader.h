#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <QDate>

struct Geolocation
{
    float latitude;
    float longtitude;
};

using DataTable = std::vector<std::vector<std::string>>;
using CountryIndexMap = std::unordered_map<std::string, int>;
using CountryGeolocationMap = std::unordered_map<std::string,Geolocation>;
using IndexDateMap = std::unordered_map<int,QDate>;

class FileReader
{
    std::string fileName;
    DataTable values;
    CountryIndexMap countryIndex;
    CountryGeolocationMap countryGeolocation;
    IndexDateMap indexDate;

public:
    FileReader(const std::string& fileToReadName);
    void read();
    void getCountryIndices();
    void getCountryGeolocation();
    void getDateIndices();
};

#endif // FILEREADER_H

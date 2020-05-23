#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <QDate>


//struct Geolocation
//{
//    float latitude;
//    float longtitude;
//};

using DataTable = std::vector<std::vector<std::string>>;
using CountryIndexMap = std::unordered_map<std::string, int>;
using CountryGeolocationMap = std::unordered_map<std::string,std::pair<float,float>>;
using IndexDateMap = std::unordered_map<int,QDate>;
using RawDataTable = std::vector<std::vector<int>>;

class FileReader
{
    std::string fileName;
    DataTable values;
    CountryIndexMap countryIndex;
    CountryGeolocationMap countryGeolocation;
    IndexDateMap indexDate;
    RawDataTable rawData;

public:
    FileReader(const std::string& fileToReadName);
    void read();
    void readCountryIndices();
    void readCountryGeolocation();
    void readDateIndices();
    void readRawData();
    CountryIndexMap getCountryIndex() const;
    CountryGeolocationMap getCountryGeolocation() const;
    IndexDateMap getIndexDate() const;
    RawDataTable getRawData() const;
};

#endif // FILEREADER_H

#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <QDate>

//struct Geolocation
//{
//    float latitude;
//    float longtitude;
//};

using CountryIndexMap = std::unordered_map<std::string, int>;
//using CountryGeolocationMap = std::unordered_map<std::string,Geolocation>;
using IndexDateMap = std::unordered_map<int,QDate>;
using RawDataTable = std::vector<std::vector<int>>;


class DataHolder
{
    CountryIndexMap countryIndexMap;
    //CountryGeolocationMap countryGeolocationMap;
    IndexDateMap indexDateMap;
    RawDataTable data;

public:
    DataHolder(CountryIndexMap ci, IndexDateMap id, RawDataTable d);
    CountryIndexMap getCountryIndexMap() const;
    IndexDateMap getIndexDateMap() const;
    RawDataTable getData() const;
};

#endif // DATAHOLDER_H

#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <QDate>

//struct Location
//{
//    float latitude;
//    float longtitude;
//};



using CountryIndexMap = std::unordered_map<std::string, int>;
using CountryGeolocationMap = std::unordered_map<std::string,std::pair<float,float>>;
using IndexDateMap = std::unordered_map<int,QDate>;
using RawDataTable = std::vector<std::vector<int>>;


class DataHolder
{
    CountryIndexMap countryIndexMap;
    IndexDateMap indexDateMap;
    RawDataTable data;
    CountryGeolocationMap countryGeolocationMap;

public:
    DataHolder(CountryIndexMap ci, IndexDateMap id, RawDataTable d, CountryGeolocationMap cg);
    CountryIndexMap getCountryIndexMap() const;
    IndexDateMap getIndexDateMap() const;
    RawDataTable getData() const;
    CountryGeolocationMap getCountryGeolocationMap() const;
};

#endif // DATAHOLDER_H

#include "filereader.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <QDebug>

CountryIndexMap FileReader::getCountryIndex() const
{
    return countryIndex;
}

CountryGeolocationMap FileReader::getCountryGeolocation() const
{
    return countryGeolocation;
}

IndexDateMap FileReader::getIndexDate() const
{
    return indexDate;
}

RawDataTable FileReader::getRawData() const
{
    return rawData;
}

FileReader::FileReader(const std::string &fileToReadName)
    : fileName(fileToReadName)
{}

void FileReader::read()
{
    std::ifstream fin(fileName);
    if(!fin) qDebug() << "Cos nie halo - brak pliku/nie można odczytac";

    for (std::string line; std::getline(fin, line); )
    {
        std::string toReplace = "\"Korea, South\"";
        auto indexToReplace = line.find(toReplace);
        if(indexToReplace != std::string::npos)
        {
        line.replace(indexToReplace,toReplace.length(),"Korea South");
        }
        toReplace = "\"Bonaire, Sint Eustatius and Saba\"";
        indexToReplace = line.find(toReplace);
        if(indexToReplace != std::string::npos)
        {
        line.replace(indexToReplace,toReplace.length(),"Bonaire Sint Eustatius and Saba");
        }
        //std::replace(line.begin(),line.end(),"")
        std::replace(line.begin(), line.end(), ' ', '-');
        if(line.at(0) == ',') line.insert(line.cbegin(),'#');
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        values.push_back(
                    std::vector<std::string>(std::istream_iterator<std::string>(in),
                                             std::istream_iterator<std::string>()));
    }
}

void FileReader::readCountryIndices()
{
    //qDebug() << values.size();
    for(auto i = 1u; i < values.size(); ++i)
    {
        std::string countryAndRegion = values.at(i).at(1);
        std::replace(countryAndRegion.begin(),countryAndRegion.end(), '-',' ');

        if(values.at(i).at(0) != "#")
        {
            std::string region = values.at(i).at(0);
            std::replace(region.begin(), region.end(), '-', ' ');
            countryAndRegion.append(" - ").append(region);
        }
        //qDebug() << countryAndRegion.c_str() << i-1;

        countryIndex.insert({countryAndRegion,i-1});
    }

//    for(auto a : countryIndex)
//    {
//        qDebug() << a.first.c_str() <<" "<<a.second<<"\n";
//    }
}

void FileReader::readCountryGeolocation()
{
    for(auto i = 1u; i < values.size();++i)
    {
        std::string countryAndRegion = values.at(i).at(1);

        if(values.at(i).at(0) != "#")
        {
            std::string region = values.at(i).at(0);
            std::replace(region.begin(), region.end(), '-', ' ');
            countryAndRegion.append(" - ").append(region);
        }
        qDebug() << values.at(i).at(2).c_str() <<values.at(i).at(3).c_str();

        std::string latitude = values.at(i).at(2);
        std::string longtitude = values.at(i).at(3);

        std::replace(latitude.begin(),latitude.end(),'.',',');
        std::replace(longtitude.begin(),longtitude.end(),'.',',');

        countryGeolocation.insert({countryAndRegion,{std::stof(latitude),std::stof(longtitude)}});
    }

    for(auto a : countryGeolocation)
    {
        qDebug() << a.first.c_str() <<" "<<a.second.first<<" "<<a.second.second<<"\n";
    }
}

void FileReader::readDateIndices()
{
    for(auto i = 4u, j = 0u; i < values.at(0).size(); ++i, ++j)
    {
        QDate date = QDate::fromString(values.at(0).at(i).append("20").c_str(),"M/d/yyyy");
        indexDate.insert({j, date});
    }

//    for(auto a : indexDate)
//    {
//        qDebug() << a.first <<" "<<a.second;
//    }
}

void FileReader::readRawData()
{
    for(auto i = 1u; i < values.size(); ++i)
    {
        std::vector<int> temp;
        for(auto j = 4u; j < values.at(i).size();++j)
        {
            temp.push_back(std::stoi(values.at(i).at(j).c_str()));
        }
        rawData.push_back(temp);
    }

//    for(const auto& a :rawData)
//    {
//        for(const auto& b : a )
//        {
//            qDebug() << b;
//        }
//        qDebug() << "\n";
//    }
}

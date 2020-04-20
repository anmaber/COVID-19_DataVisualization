#include "dataholder.h"

CountryIndexMap DataHolder::getCountryIndexMap() const
{
    return countryIndexMap;
}

IndexDateMap DataHolder::getIndexDateMap() const
{
    return indexDateMap;
}

RawDataTable DataHolder::getData() const
{
    return data;
}

DataHolder::DataHolder(CountryIndexMap ci, IndexDateMap id, RawDataTable d)
    : countryIndexMap(ci),
      indexDateMap(id),
      data(d)
{}

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

CountryGeolocationMap DataHolder::getCountryGeolocationMap() const
{
    return countryGeolocationMap;
}

DataHolder::DataHolder(CountryIndexMap ci, IndexDateMap id, RawDataTable d, CountryGeolocationMap cg)
    : countryIndexMap(ci),
      indexDateMap(id),
      data(d),
      countryGeolocationMap(cg)
{}

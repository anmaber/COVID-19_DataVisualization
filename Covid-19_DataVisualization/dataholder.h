#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <QDate>

/*!
 * \file
 * \brief Zawiera definicję klasy DataHolder
 *
 * Plik zawiera definicję klasy DataHolder.
 */

using CountryIndexMap = std::unordered_map<std::string, int>;
using CountryGeolocationMap = std::unordered_map<std::string,std::pair<float,float>>;
using IndexDateMap = std::unordered_map<int,QDate>;
using RawDataTable = std::vector<std::vector<int>>;

/*!
 * \brief Klasa modelująca obekt przechowujący dane o przypadkach.
 *
 * Klasa modeluje obiekt przechowujący dane odnośnie przypadków.
 * Składa się z różnych struktur.
 */

class DataHolder
{
    /*!
     * \brief Mapa krajów i ich indeksów.
     */
    CountryIndexMap countryIndexMap;
    /*!
     * \brief Mapa indeksów i dat przypisanych do nich.
     */
    IndexDateMap indexDateMap;
    /*!
     * \brief Wektor wektorów przechowujący dane odnośnie ilości przypadków.
     */
    RawDataTable data;
    /*!
     * \brief Mapa przechowująca nazwy krajów i ich geolokacje.
     */
    CountryGeolocationMap countryGeolocationMap;

public:
    /*!
     * \brief Konstruktor parametryczny.
     *
     * Przyjmuje przez wartość struktury danych, które ma przechowywać
     * \param[in] ci - mapa krajów i ich indeksów
     * \param[in] id - mapa indeksów i dat przypisanych do nich
     * \param[in] d - wektor wektorów przechowujących dane odnośnie przypadków
     * \param[in] cg - mapa krajów i ich geolokalizacji
     */
    DataHolder(CountryIndexMap ci, IndexDateMap id, RawDataTable d, CountryGeolocationMap cg);
    /*!
     * \brief Zwraca przechowywaną mapę krajów i ich indeksów (DataHolder::countryIndexMap).
     * \return mapa krajów i ich indeksów
     */
    CountryIndexMap getCountryIndexMap() const;
    /*!
     * \brief Zwraca przechowywaną mapę indeksów i dat.
     * \return mapa indeksów i przypisanych do nich dat (DataHolder::indexDateMap)
     */
    IndexDateMap getIndexDateMap() const;
    /*!
     * \brief Zwraca wektor wektorów przechowujących dane odnośnie przypadków (DataHolder::RawDataTable).
     * \return wektor wektorów przechowujących dane odnośnie przypadków.
     */
    RawDataTable getData() const;
    /*!
     * \brief Zwraca przechowywaną mapę krajów i ich geolokalizacji (DataHolder::countryGeolocationMap).
     * \return mapa krajów i ich geolokalizacji
     */
    CountryGeolocationMap getCountryGeolocationMap() const;
};

#endif // DATAHOLDER_H

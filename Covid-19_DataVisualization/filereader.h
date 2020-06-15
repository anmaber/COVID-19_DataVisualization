#ifndef FILEREADER_H
#define FILEREADER_H

/*!
 * \file
 * \brief Definicja klasy FileReader
 *
 * Plik zawiera definicję klasy FileReader.
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <QDate>

using DataTable = std::vector<std::vector<std::string>>;
using CountryIndexMap = std::unordered_map<std::string, int>;
using CountryGeolocationMap = std::unordered_map<std::string,std::pair<float,float>>;
using IndexDateMap = std::unordered_map<int,QDate>;
using RawDataTable = std::vector<std::vector<int>>;

/*!
*\brief Modeluje obiekt, który sczytuje dane z pliku.
*
*Modeluje obiekt, który sczytuje dane z plików w formacie csv oraz przechowuje te dane w odpowiednich strukturach.
*Struktura plików obsługiwanych przez FileReader jest następująca:
*- pierwszy wiersz stanowią nagłówki kolumn,
*- w pierwszej kolumnie znajduje się prowincja (może być pusta),
*- w drugiej kolumnie znajduje się kraj,
*- w trzeciej kolumnie znajduje się szerokość geograficzna kraju bądź prowincji,
*- w czwartej kolumnie znajduje się długość geograficzna kraju bądź prowincji,
*- w pozostałych kolumnach znajduje się liczba przypadków w danym kraju bądź prowincji w danym dniu.
*/
class FileReader
{
    /*!
     * \brief fileName - nazwa pliku do odczytu
     */
    std::string fileName;
    /*!
     * \brief values - wszystkie wartości z pliku csv zapisane w wektorze wektorów.
     */
    DataTable values;
    /*!
     * \brief countryIndex - mapa krajów i ich indeksów.
     *
     */
    CountryIndexMap countryIndex;
    /*!
     * \brief countryGeolocation - mapa krajów i icg geolokalizacji.
     */
    CountryGeolocationMap countryGeolocation;
    /*!
     * \brief indexDate - mapa indeksów i dat.
     */
    IndexDateMap indexDate;
    /*!
     * \brief rawData -  wektor wektorów z liczbami przypadków.
     */
    RawDataTable rawData;

public:
    /*!
     * \brief Konstruktor parametryczny przyjmujący nazwę pliku.
     *
     * Konstruktor parametryczny klasy FileReader. Ustawia FileReader::fileName na fileToReadName.
     *
     * \param[in] fileToReadName - nazwa pliku do odczytu.
     *
     */
    FileReader(const std::string& fileToReadName);

    /*!
     * \brief Metoda wczytująca plik.
     *
     * W metodzie otwierany jest plik csv a następnie parsowany do FileReade::values.
     */
    void read();
    /*!
     * \brief Metoda przypisująca krajom indeksy.
     *
     * W metodzie wyodrębniane z FileReader::values są kraj, prowincja oraz indeks.Nazwa kraju i prowincji tworzą unikalną nazwę.
     *  Do nazwy przypisywany jest indeks.
     *  Para jest przechowywana w FileReader::countryIndex.
     */
    void readCountryIndices();
    /*!
     * \brief Metoda przypisująca krajom ich geolokację.
     *
     * W metodzie wyodrębniane z FileReader::values są kraj, prowincja i współrzedne geograficzne.
     * Nazwa kraju jest łączona z nazwą prowincji. Tworzy ona unikalną nazwę.
     *  Do nazwy przypisywana jest geolokacja.
     *  Para jest przechowywana w FileReader::countryGeolocation.
     */
    void readCountryGeolocation();
    /*!
     * \brief Metoda przypisująca datom ich indeksy.
     *
     * W metodzie wyodrębniane z FileReader::values są data oraz indeks. Tworzą one unikalną parę.
     * Para jest przechowywana w FileReader::DateIndices.
     */
    void readDateIndices();
    /*!
     * \brief Metoda wyodrębniająca surowe dane.
     *
     * W metodzie są wyodrębniane dane odnośnie ilości przypadków z FileReader::values.
     * Są one zapisywane do FileReader::rawData.
     */
    void readRawData();
    /*!
     * \brief Metoda zwraca mapę nazw kraju i indeksów.
     * \return mapa nazw krajów i indeksów
     */
    CountryIndexMap getCountryIndex() const;
    /*!
     * \brief Metoda zwraca mapę nazw kraju i ich geolokalizacji.
     * \return mapa nazw krajów i ich geolokalizacji
     */
    CountryGeolocationMap getCountryGeolocation() const;
    /*!
     * \brief Metoda zwraca mapę indeksów i dat.
     * \return mapa indeksów i dat
     */
    IndexDateMap getIndexDate() const;
    /*!
     * \brief Metoda zwraca wektor wektorów zawierających liczby przypadków.
     * \return  wektor wektorów zawierających liczby przypadków
     */
    RawDataTable getRawData() const;
};

#endif // FILEREADER_H

#ifndef BASICANALYSISWIGET_H
#define BASICANALYSISWIGET_H
/*!
 * \file
 * \brief Definicja klasy basicAnalysisWiget.
 *
 * Plik zawiera definicję klasy basicAnalysisWiget.
 */

#include <QWidget>
#include <QStringList>
#include "dataholder.h"
#include "qcustomplot.h"

namespace Ui {
class basicAnalysisWiget;
}

/*!
 * \brief Modeluje odbiekt odpowiedzialny za widok analizy.
 *
 * Modeluje obiekt, który przedstawia na wykresie oraz za pomocą liczb dane odnośnie zachorowań na COVID-19.
 * Dane zależą od wybranych opcji.
 */
class basicAnalysisWiget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor parametryczny klasy basicAnalysisWiget.
     *
     * Inicjalizuje basicAnalysisWiget::ui oraz wykres, ustawia basicAnalysisWiget::cases, basicAnalysisWiget::deaths
     * oraz basicAnalysisWiget::recoveries. Sczyczuje listę krajów z jednego z obiektów typu DataHolder i ustawia ją w liście rozwijanej. Ustawia maksymalną datę
     * w polach do zmiany dat.
     *
     * \param[in] parent - rodzic dla widgetu
     * \param[in] cases - wskaźnik na obiekt klasy DataHolder, który przechowuje dane zwiazane z zachorowaniami
     * \param[in] deaths - wskaźnik na obiekt klasy DataHolder, który przechowuje dane związane ze zgonami
     * \param[in] recoveries - wskaźnik na obiekt klasy DataHolder, który przechowuje dane związane z wyzdrowieniami
     */
    explicit basicAnalysisWiget(QWidget *parent = 0,DataHolder* cases = nullptr,
                                DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);
    ~basicAnalysisWiget();

private slots:
    /*!
     * \brief Slot reagujący na zmianę daty końcowej.
     *
     * Gdy zostanie zmieniona data końcowa, zostanie zaktualizowana maksymalna data początkowa oraz zostaną zaktualizowane wykresy.
     * \param[in] date - data na którą została zmieniona poprzednia
     */
    void on_dateEdit_dateChanged(const QDate &date);

    /*!
     * \brief Slot reagujący na zmianę kraju.
     *
     * Gdy zostanie zmieniony kraj zostaną zaktualizowane wykresy
     * \param[in] countryName - nazwa kraju na którą została zmieniona poprzednia
     */
    void on_comboBox_currentIndexChanged(const QString &countryName);

    //void on_checkBox_clicked();

    /*!
     * \brief Slot reagujący na kliknięcie na pole wyboru związane z wyzgrowieniami.
     *
     * Gdy zostanie kliknięte pole wyboru związane z wyzgrowieniami, wykresy oraz pola z liczbami zostaną zaktualizowane
     */
    void on_checkRecoveries_clicked();

    /*!
     * \brief Slot reagujący na kliknięcie na pole wyboru związane ze zgonami.
     *
     * Gdy zostanie kliknięte pole wyboru związane ze zgonami, wykresy oraz pola z liczbami zostaną zaktualizowane
     */
    void on_checkDeaths_clicked();

    /*!
     * \brief Slot reagujący na zmianę daty początkowej.
     *
     * Gdy zostanie zmieniona data początkowa, zostaną zaktualizowane wykresy.
     * \param[in] date - data na którą została zmieniona poprzednia
     */
    void on_dateEditStart_dateChanged(const QDate &startDate);



    /*!
     * \brief Slot reagujący na kliknięcie na pole wyboru związane z zachorowaniami.
     *
     * Gdy zostanie kliknięte pole wyboru związane z zachorowaniami, wykresy oraz pola z liczbami zostaną zaktualizowane
     */
    void on_checkBox_clicked();

private:
    /*!
     * \brief Interfejs użytkownika zaprojektowany w Designerze.
     */
    Ui::basicAnalysisWiget *ui;
    /*!
     * \brief Wskaźnik na strukturę przechowująca dane odnośnie zachorowań.
     */
    DataHolder*  cases;
    /*!
     * \brief Wskaźnik na strukturę przechowująca dane odnośnie zgonów.
     */
    DataHolder * deaths;
    /*!
     * \brief Wskaźnik na strukturę przechowująca dane odnośnie wyzdrowień.
     */
    DataHolder * recoveries;
    /*!
     * \brief Tytuł wykresu.
     */
    QCPTextElement *title;

    /*!
     * \brief Lista krajów dla których dostępne są dane.
     */
    QStringList countries;

    /*!
     * \brief Metoda odpowiedzialna za inicjalizację wykresu.
     *
     * Na pole wykresu są dodawane trzy wykresy. Ustawiane są opisy osi oraz tytuł wykresu.
     * Oś pozioma jest formatowana tak aby pokazywać daty. Pokazywana jest również legenda.
     */
    void setUpPlot();
    /*!
     * \brief Metoda odpowiedzialna za aktualizację wizualizacji danych.
     *
     * Wyświetlane są odpowiednie dane w zależności od kraju i wybranych dat.
     * Sprawdzane jest jakie dane mają zostać wyświetlone na wykresach.
     * Wyświetlane są odpowiednie wykresy i jest dopasowywany tytuł w zależności od wybranych parametrów.
     *
     * \param[in] date - data końcowa
     * \param[in] startDate - data początkowa
     * \param[in] country - kraj dla którego mają być zwizualizowane dane
     */
    void setData(const QDate& date, const QDate &startDate, const QString& country);
    /*!
     * \brief Metoda odnajdująca indeks kraju.
     *
     * Metoda przeszukuje mapę podaną jako parametr aby znaleźć kraj również podany jako parametr. Zwraca indeks przypisany do kraju.
     * \param[in] countryName - nazwa kraju
     * \param[in] cimap - mapa zawierająca pary krajów i indeksów
     * \return indeks szukanego kraju
     */
    int getCountryIndex(const QString &countryName, const std::unordered_map<std::string, int> &cimap);

    /*!
     * \brief Metoda odnajdująca indeks daty.
     *
     * Metoda przeszukuje mapę podaną jako parametr aby znaleźć indeks daty zadanej jako parametr.
     * \param[in] date - data
     * \param[in] idmap - mapa indeksów i dat
     * \return indeks szukanej daty
     */
    int getDateIndex(const QDate &date, const std::unordered_map<int, QDate> &idmap);
};

#endif // BASICANALYSISWIGET_H

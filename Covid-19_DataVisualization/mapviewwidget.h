#ifndef MAPVIEWWIDGET_H
#define MAPVIEWWIDGET_H
/*!
 * \file
 * \brief Definicja klasy mapViewWidget.
 *
 * Plik zawiera definicję klasy mapViewWidget.
 */
#include <QWidget>
#include <QQuickView>
#include <QLabel>
#include "dataholder.h"

namespace Ui {
class mapViewWidget;
}
/*!
 * \brief Modeluje odbiekt odpowiedzialny za widok mapy.
 *
 * Modeluje obiekt, który przedstawia mapę na której wyświetlają się koła wizualizujące ilość przypadków związanych z COVID-19.
 * Dane zależą od wybranych opcji.
 */
class mapViewWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor parametryczny klasy mapViewWiget.
     *
     * Inicjalizuje mapViewWidget::ui oraz mapę, ustawia mapViewWidget::cases, mapViewWidget::deaths
     * oraz mapViewWidget::recoveries. Umieszcza na mapie
     *
     * \param[in] parent - rodzic dla widgetu
     * \param[in] cases - wskaźnik na obiekt klasy DataHolder, który przechowuje dane zwiazane z zachorowaniami
     * \param[in] deaths - wskaźnik na obiekt klasy DataHolder, który przechowuje dane związane ze zgonami
     * \param[in] recoveries - wskaźnik na obiekt klasy DataHolder, który przechowuje dane związane z wyzdrowieniami
     */
    explicit mapViewWidget(QWidget *parent = 0,DataHolder* cases = nullptr,
                           DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);
    ~mapViewWidget();

private slots:
    /*!
     * \brief Slot reagujący na kliknięcie na przyciks wyboru związany ze zgonami.
     */
    void on_radioButtonDeaths_clicked();
    /*!
     * \brief Slot reagujący na kliknięcie na przyciks wyboru związany z przypadkami.
     */
    void on_radioButtonCases_clicked();
    /*!
     * \brief Slot reagujący na kliknięcie na przyciks wyboru związany z wyzdrowieniami.
     */
    void on_radioButtonRecoveries_clicked();
    /*!
     * \brief Slot reagujący na zmianę wartości na suwaku.
     */
    void on_horizontalSlider_valueChanged(int value);

private:
    /*!
     * \brief Dodaje na mapę nowe obiekty o zadanym kolorze
     * Dodaje na mapę koła o promieniu 0 i zadanym kolorze.
     * \param[in] color - kolor obiektu dodawanego na mapę
     */
    void addItemsOnMap(QString color);
    /*!
     * \brief stawia promienie kół znajdujących się na mapie na 0.
     */
    void deleteCircles();
    /*!
     * \brief Rysuje koła na mapie.
     *
     * Metoda rysuje koła na mape, których promień odpowiada ilości przypadków w danej dacie.
     * Date funkcja otrzymuje poprzez przeszukanie mapy z indeksami i datami. Szukany indeks to parametr value.
     * Rysowanie to zmiana właściwości koła - zmienienie jego promienia.
     *
     * \param[in] Indeks po którym funkcja szuka daty aby odczytać liczbe przypadków.
     */
    void drawCircles(int value);

    /*!
     * \brief Interfejs użytkownika zaprojektowany w Designerze.
     */
    Ui::mapViewWidget *ui;
    /*!
     * \brief Umożliwia wykorzystanie mapy zaimplementowanej w QML.
     */
    QQuickView* w;
    /*!
     * \brief Widget umożliwiający wyświetanie mapy.
     */
    QWidget* container;
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
     * \brief Wskaźnik na aktualnie używaną strukturę z danymi.
     */
    DataHolder * current;
};

#endif // MAPVIEWWIDGET_H

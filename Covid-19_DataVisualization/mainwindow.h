#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <basicanalysis.h>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QQuickView>
#include <basicanalysiswiget.h>
#include "mapviewwidget.h"
//#include <QDeclarativeView>

/*!
 * \file
 * \brief definicja klasy MainWindow
 *
 * Plik zawiera definicję klasy MainWindow.
 */

namespace Ui {
class MainWindow;
}

/*!
 * \brief Modeluje obiekt, który jest głównym oknem programu.
 *
 * Modeluje obiekt, który jest głównym oknem programu. Umożliwia dostęp do widoku analizy oraz widoku mapy.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    /*!
     * \brief Wskaźnik na widget implementujący widok mapy.
     */
    mapViewWidget *view;
    /*!
     * \brief Rozkład okna głównego.
     */
    QVBoxLayout * myLayout;
    /*!
     * \brief Widget umożliwiający użycie kart.
     */
    QTabWidget * tabs;

    /*!
     * \brief Wskaźnik na widget implementujący widok mapy.
     */
    basicAnalysisWiget *banal;


public:
    /*!
     * \brief Konstruktor parametryczny klasy MainWindow.
     *
     * Inicjalizuje MainWindow::ui oraz ustawia zakładki na odpowiednie widoki.
     * \param[in] Rodzic widgetu.
     * \param[in] Wskaźnik na obiekt typu DataHolder przechowujący dane o przypadkach.
     * \param[in] Wskaźnik na obiekt typu DataHolder przechowujący dane o zgonach.
     * \param[in] Wskaźnik na obiekt typu DataHolder przechowujący dane o wyzdrowieniach.
     */
    explicit MainWindow(QWidget *parent = 0,DataHolder* cases = nullptr,
                        DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);
    ~MainWindow();

private:
    /*!
     * \brief Interfejs zaprojektowany w designerze.
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

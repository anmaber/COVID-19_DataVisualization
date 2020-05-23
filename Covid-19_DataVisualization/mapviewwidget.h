#ifndef MAPVIEWWIDGET_H
#define MAPVIEWWIDGET_H

#include <QWidget>
#include <QQuickView>
#include "dataholder.h"

namespace Ui {
class mapViewWidget;
}

class mapViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mapViewWidget(QWidget *parent = 0,DataHolder* cases = nullptr,
                           DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);
    ~mapViewWidget();

private slots:
    void on_radioButtonDeaths_clicked();

    void on_radioButtonCases_clicked();

    void on_radioButtonRecoveries_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    void addItemsOnMap(QString color);
    void deleteCircles();
    void drawCircles(int value);

    Ui::mapViewWidget *ui;
    QQuickView* w;
    QWidget* container;
    DataHolder*  cases;
    DataHolder * deaths;
    DataHolder * recoveries;
    DataHolder * current;
};

#endif // MAPVIEWWIDGET_H

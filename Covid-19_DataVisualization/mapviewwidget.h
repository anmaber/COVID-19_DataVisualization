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
    void on_horizontalSlider_sliderMoved(int position);
    void on_radioButtonDeaths_clicked();

    void on_radioButtonCases_clicked();

private:
    Ui::mapViewWidget *ui;
    QQuickView* w;
    QWidget* container;
    DataHolder*  cases;
    DataHolder * deaths;
    DataHolder * recoveries;
};

#endif // MAPVIEWWIDGET_H

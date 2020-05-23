#ifndef MAPVIEWWIDGET_H
#define MAPVIEWWIDGET_H

#include <QWidget>
#include <QQuickView>

namespace Ui {
class mapViewWidget;
}

class mapViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mapViewWidget(QWidget *parent = 0);
    ~mapViewWidget();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_radioButton_2_clicked();

    void on_radioButtonDeaths_clicked();

private:
    QQuickView* w;
    QWidget* container;
    Ui::mapViewWidget *ui;
};

#endif // MAPVIEWWIDGET_H

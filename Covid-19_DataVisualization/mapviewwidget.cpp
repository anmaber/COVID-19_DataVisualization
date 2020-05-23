#include "mapviewwidget.h"
#include "ui_mapviewwidget.h"
#include <QMetaObject>

mapViewWidget::mapViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mapViewWidget)
{
    ui->setupUi(this);
    w = new QQuickView;
    w->setSource(QUrl("../myMap.qml"));
    ui->container = QWidget::createWindowContainer(w,this);
    ui->container->setFocusPolicy(Qt::TabFocus);
    ui->container->resize(500,400);


    QObject *m = w->findChild<QObject*>("map");
    if (m)
    {
        qDebug()<<"WESZLO";
        QMetaObject::invokeMethod(m, "addCircle",

                Q_ARG(QVariant, "red"),Q_ARG(QVariant, "dupa"), Q_ARG(QVariant, 50000.0), Q_ARG(QVariant,0.0), Q_ARG(QVariant,153.0));
    }



   // w->show();
}

mapViewWidget::~mapViewWidget()
{
    delete ui;
}

void mapViewWidget::on_horizontalSlider_sliderMoved(int position)
{
    int rad = position * 1000;
    QStringList l = {"dupa","circ"};
    for(auto n : l)
    {
        QObject *circ = w->findChild<QObject*>(n);
        if (circ)
            circ->setProperty("radius",rad);
    }

}

void mapViewWidget::on_radioButton_2_clicked()
{
    QObject *m = w->findChild<QObject*>("map");
    if (m)
    {
         QMetaObject::invokeMethod(m, "clearMapItems");
    }
}

void mapViewWidget::on_radioButtonDeaths_clicked()
{
    QObject *m = w->findChild<QObject*>("map");
    if (m)
    {
         QMetaObject::invokeMethod(m, "clearMapItems");
    }
}

#include "mapviewwidget.h"
#include "ui_mapviewwidget.h"
#include <QMetaObject>

mapViewWidget::mapViewWidget(QWidget *parent, DataHolder *cases, DataHolder *deaths, DataHolder *recoveries) :
    QWidget(parent),
    ui(new Ui::mapViewWidget),
    cases(cases),
    deaths(deaths),
    recoveries(recoveries)
{
    ui->setupUi(this);
    w = new QQuickView;
    w->setSource(QUrl("../myMap.qml"));
    ui->container = QWidget::createWindowContainer(w,this);
    ui->container->setFocusPolicy(Qt::TabFocus);
    ui->container->resize(500,400);

    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(cases->getIndexDateMap().size()-1);
    qDebug()<<"MAX:" << ui->horizontalSlider->maximum();
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
    qDebug()<<position;

}

void mapViewWidget::on_radioButtonDeaths_clicked()
{
    QObject *m = w->findChild<QObject*>("map");
    if (m)
    {
        QMetaObject::invokeMethod(m, "clearMapItems");
    }
}

void mapViewWidget::on_radioButtonCases_clicked()
{
    QString color = "red";
    QObject *m = w->findChild<QObject*>("map");
    if (m)
    {
        QMetaObject::invokeMethod(m, "clearMapItems");


        for(auto cg : cases->getCountryGeolocationMap())
        {
            QString name = QString::fromStdString(cg.first);
            int lat = cg.second.first;
            int lon = cg.second.second;
            QMetaObject::invokeMethod(m, "addCircle",

                                      Q_ARG(QVariant, color),Q_ARG(QVariant, name), Q_ARG(QVariant, 50000.0), Q_ARG(QVariant,lat), Q_ARG(QVariant,lon));
        }
    }
}

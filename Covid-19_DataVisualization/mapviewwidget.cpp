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
    ui->container->resize(800,512);

    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(deaths->getIndexDateMap().size()-1);
    qDebug()<<"MAX:" << ui->horizontalSlider->maximum();


    QObject *m = w->findChild<QObject*>("map");
    if (m)
    {
      for(auto cg : cases->getCountryGeolocationMap())
        {
            QString name = QString::fromStdString(cg.first) + "c";
            qDebug() <<name;
            int lat = cg.second.first;
            int lon = cg.second.second;
            QMetaObject::invokeMethod(m, "addCircle",

                                      Q_ARG(QVariant, "red"),Q_ARG(QVariant, name), Q_ARG(QVariant,0.0), Q_ARG(QVariant,lat), Q_ARG(QVariant,lon));
        }

        for(auto cg : deaths->getCountryGeolocationMap())
        {
            QString name = QString::fromStdString(cg.first) + "d";
            qDebug() <<name;
            int lat = cg.second.first;
            int lon = cg.second.second;
            QMetaObject::invokeMethod(m, "addCircle",

                                      Q_ARG(QVariant, "black"),Q_ARG(QVariant, name), Q_ARG(QVariant,0.0), Q_ARG(QVariant,lat), Q_ARG(QVariant,lon));
        }
        for(auto cg : recoveries->getCountryGeolocationMap())
        {
            QString name = QString::fromStdString(cg.first) + "r";
            qDebug() <<name;
            int lat = cg.second.first;
            int lon = cg.second.second;
            QMetaObject::invokeMethod(m, "addCircle",

                                      Q_ARG(QVariant, "green"),Q_ARG(QVariant, name), Q_ARG(QVariant,0.0), Q_ARG(QVariant,lat), Q_ARG(QVariant,lon));
        }
    }
}

mapViewWidget::~mapViewWidget()
{
    delete ui;
}

void mapViewWidget::on_radioButtonDeaths_clicked()
{
    current = deaths;
    deleteCircles();
    drawCircles( ui->horizontalSlider->value());
}

void mapViewWidget::on_radioButtonCases_clicked()
{
    current = cases;
    deleteCircles();
    drawCircles( ui->horizontalSlider->value());
}

void mapViewWidget::addItemsOnMap(QString color)
{
    QObject *m = w->findChild<QObject*>("map");
    if (m)
    {
        QMetaObject::invokeMethod(m, "clearMapItems");


        for(auto cg : current->getCountryGeolocationMap())
        {
            QString name = QString::fromStdString(cg.first);
            int lat = cg.second.first;
            int lon = cg.second.second;
            int position = ui->horizontalSlider->value();

            auto countryIndexiter = current->getCountryIndexMap().find(cg.first);
            int countryIndex = countryIndexiter->second;
            int rad = current->getData().at(countryIndex).at(position);
            QMetaObject::invokeMethod(m, "addCircle",

                                      Q_ARG(QVariant, color),Q_ARG(QVariant, name), Q_ARG(QVariant, rad), Q_ARG(QVariant,lat), Q_ARG(QVariant,lon));
        }
    }
}

void mapViewWidget::deleteCircles()
{
    for(auto n : cases->getCountryGeolocationMap())
    {
        QString countryName = QString::fromStdString(n.first)+"c";
        QObject *circ = w->findChild<QObject*>(countryName);
        if (circ)
            circ->setProperty("radius",0);
    }
    for(auto n : deaths->getCountryGeolocationMap())
    {
        QString countryName = QString::fromStdString(n.first)+"d";
        QObject *circ = w->findChild<QObject*>(countryName);
        if (circ)
            circ->setProperty("radius",0);
    }
    for(auto n : recoveries->getCountryGeolocationMap())
    {
        QString countryName = QString::fromStdString(n.first)+"r";
        QObject *circ = w->findChild<QObject*>(countryName);
        if (circ)
            circ->setProperty("radius",0);
    }

}

void mapViewWidget::drawCircles(int value)
{
    QString appendix;

    if(ui->radioButtonCases->isChecked())
    {
        appendix = "c";
    }
    if(ui->radioButtonDeaths->isChecked())
    {
        appendix = "d";
    }
    if(ui->radioButtonRecoveries->isChecked())
    {
        appendix= "r";
    }
    for(auto n : current->getCountryGeolocationMap())
    {
        qDebug()<<QString::fromStdString(n.first);
        auto countryIndexiter = current->getCountryIndexMap().find(n.first);

        int countryIndex = countryIndexiter->second;
        int rad =current->getData().at(countryIndex).at(value);
        QString countryName = QString::fromStdString(n.first)+appendix;
        QObject *circ = w->findChild<QObject*>(countryName);
        if (circ)
            circ->setProperty("radius",rad);
    }
    qDebug()<<value;
}


void mapViewWidget::on_radioButtonRecoveries_clicked()
{
    current = recoveries;
    deleteCircles();
    drawCircles( ui->horizontalSlider->value());
}

void mapViewWidget::on_horizontalSlider_valueChanged(int value)
{
    drawCircles(value);
}

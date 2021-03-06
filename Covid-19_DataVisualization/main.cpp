#include "mainwindow.h"
#include <QApplication>
#include <filereader.h>
#include <QDebug>
//#include "basicanalysis.h"
//#include "analysismainwindow.h"
#include "dataholder.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    system("./../downloadData.sh");

    FileReader casesReader("confirmed.csv");
    casesReader.read();
    casesReader.readDateIndices();
    casesReader.readCountryIndices();
    casesReader.readRawData();
    qDebug() << "GEOLOKACJA";
    casesReader.readCountryGeolocation();
    DataHolder*cases = new DataHolder(casesReader.getCountryIndex(),casesReader.getIndexDate(),casesReader.getRawData(),casesReader.getCountryGeolocation());

    FileReader deathsReader("deaths.csv");
    deathsReader.read();
    deathsReader.readCountryIndices();
    deathsReader.readDateIndices();
    deathsReader.readRawData();
    deathsReader.readCountryGeolocation();
    DataHolder* deaths = new DataHolder(deathsReader.getCountryIndex(),deathsReader.getIndexDate(),deathsReader.getRawData(),deathsReader.getCountryGeolocation());

    FileReader recoveriesReader("recovered.csv");
    recoveriesReader.read();
    recoveriesReader.readCountryIndices();
    recoveriesReader.readDateIndices();
    recoveriesReader.readRawData();
    recoveriesReader.readCountryGeolocation();
    DataHolder* recoveries = new DataHolder(recoveriesReader.getCountryIndex(),recoveriesReader.getIndexDate(),recoveriesReader.getRawData(),recoveriesReader.getCountryGeolocation());


   // BasicAnalysis* window = new BasicAnalysis(nullptr, cases, deaths, recoveries);
    MainWindow Mwindow(nullptr,cases, deaths, recoveries);
    Mwindow.show();

    return a.exec();

}

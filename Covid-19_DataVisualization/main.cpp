#include "mainwindow.h"
#include <QApplication>
#include <filereader.h>
#include <QDebug>
#include "basicanalysis.h"
#include "analysismainwindow.h"
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
    DataHolder*cases = new DataHolder(casesReader.getCountryIndex(),casesReader.getIndexDate(),casesReader.getRawData());

    FileReader deathsReader("deaths.csv");
    deathsReader.read();
    deathsReader.readCountryIndices();
    deathsReader.readDateIndices();
    deathsReader.readRawData();
    DataHolder* deaths = new DataHolder(deathsReader.getCountryIndex(),deathsReader.getIndexDate(),deathsReader.getRawData());

    FileReader recoveriesReader("confirmed.csv");
    recoveriesReader.read();
    recoveriesReader.readCountryIndices();
    recoveriesReader.readDateIndices();
    recoveriesReader.readRawData();
    DataHolder* recoveries = new DataHolder(recoveriesReader.getCountryIndex(),recoveriesReader.getIndexDate(),recoveriesReader.getRawData());


    BasicAnalysis window(nullptr, cases, deaths, recoveries);
    //    AnalysisMainWindow window;
    window.show();

    return a.exec();

}

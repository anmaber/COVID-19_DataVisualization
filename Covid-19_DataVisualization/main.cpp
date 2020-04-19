#include "mainwindow.h"
#include <QApplication>
#include <filereader.h>
#include <QDebug>
#include "basicanalysis.h"
#include "analysismainwindow.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    FileReader f("../confirmedCases.csv");
    f.read();
    f.readCountryIndices();
   // f.readCountryGeolocation();
    f.readDateIndices();
    f.readRawData();

    BasicAnalysis window(nullptr,f.getCountryIndex(),f.getIndexDate(),f.getRawData());
//    AnalysisMainWindow window;
    window.show();

    return a.exec();
}

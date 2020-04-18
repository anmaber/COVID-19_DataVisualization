#include "mainwindow.h"
#include <QApplication>
#include <filereader.h>
#include <QDebug>
#include "basicanalysis.h"
#include "analysismainwindow.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    AnalysisMainWindow window;
    window.show();

    FileReader f("../try.csv");
    f.read();
    f.readCountryIndices();
    f.readCountryGeolocation();
    f.readDateIndices();
    f.readRawData();

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <filereader.h>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FileReader f("../try.csv");
    f.read();
    f.readCountryIndices();
    f.readCountryGeolocation();
    f.readDateIndices();
    f.readRawData();

    return a.exec();
}

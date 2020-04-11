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
    f.getCountryIndices();
    f.getCountryGeolocation();

    return a.exec();
}

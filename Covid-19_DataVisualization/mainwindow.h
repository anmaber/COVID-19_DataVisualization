#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <basicanalysis.h>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QQuickView>
#include <basicanalysiswiget.h>
#include "mapviewwidget.h"
//#include <QDeclarativeView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //QQuickView *view;
    mapViewWidget *view;
    QWidget *container;
    QVBoxLayout * myLayout;
    QTabWidget * tabs;
    basicAnalysisWiget *banal;


public:
    explicit MainWindow(QWidget *parent = 0,DataHolder* cases = nullptr,
                        DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

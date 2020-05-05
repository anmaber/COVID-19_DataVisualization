#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <basicanalysis.h>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QQuickView>
//#include <QDeclarativeView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QQuickView *view;
    QWidget *container;
    QVBoxLayout * myLayout;
    QTabWidget * tabs;


public:
    explicit MainWindow(QWidget *parent = 0,BasicAnalysis* analiza = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, DataHolder* cases,
                       DataHolder* deaths, DataHolder* recoveries) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabs = new QTabWidget(this);
    setCentralWidget(tabs);
    myLayout = new QVBoxLayout(tabs);
    banal=new basicAnalysisWiget(nullptr,cases,deaths,recoveries);
    tabs->addTab(banal,"Analysis");

    view = new mapViewWidget(nullptr,cases,deaths,recoveries);
    tabs->addTab(view,"Map");

}

MainWindow::~MainWindow()
{
    delete ui;
}

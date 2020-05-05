#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, BasicAnalysis *analiza) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabs = new QTabWidget(this);
    setCentralWidget(tabs);
    myLayout = new QVBoxLayout(tabs);
    tabs->addTab(analiza,"Analysis");

    view = new QQuickView();
    container = QWidget::createWindowContainer(view, this);
   // container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl("../myMap.qml"));
    tabs->addTab(container,"Map");

}

MainWindow::~MainWindow()
{
    delete ui;
}

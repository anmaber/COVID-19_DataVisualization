#include "analysismainwindow.h"

AnalysisMainWindow::AnalysisMainWindow(QWidget *parent) : QMainWindow(parent)
{
    setCentralWidget(new BasicAnalysis());
    setStatusBar(new QStatusBar());
    statusBar()->showMessage(tr("Start"));
    resize(300,100);
}

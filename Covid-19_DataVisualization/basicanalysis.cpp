#include "basicanalysis.h"

BasicAnalysis::BasicAnalysis(QWidget *parent) : QWidget(parent)
{
    chooseCountryLabel = new QLabel(tr("Choose country/region: "),this);
    chooseCountryLabel->move(10,10);

    chooseCountryBox = new QComboBox(this);
    chooseCountryBox->addItem("Polska");
    chooseCountryBox->addItem("Szwajcaria");
    chooseCountryBox->move(200,10);

    resize(400,100);
}

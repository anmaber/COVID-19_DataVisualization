#include "basicanalysis.h"

BasicAnalysis::BasicAnalysis(QWidget *parent) : QWidget(parent)
{
    chooseCountryLabel = new QLabel(tr("Choose country/region: "),this);
    chooseCountryLabel->move(10,10);

    chooseCountryBox = new QComboBox(this);
    chooseCountryBox->addItem("Polska");
    chooseCountryBox->addItem("Szwajcaria");
    chooseCountryBox->move(200,10);

    chosenCountryLabel = new QLabel(tr("chosen country:"),this);
    chosenCountryLabel->move(10,40);

    chosenCountry = new QLabel(this);
    chosenCountry->move(200,40);
    chosenCountry->setFixedSize(300,20);

    connect(chooseCountryBox,SIGNAL(currentIndexChanged(QString)),chosenCountry,SLOT(setText(QString)));

    resize(400,100);
}

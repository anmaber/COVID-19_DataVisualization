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

    chosenCountry = new MyLabel(this);
    chosenCountry->move(200,40);
    chosenCountry->setFixedSize(300,20);

    connect(chooseCountryBox,SIGNAL(currentIndexChanged(QString)),chosenCountry,SLOT(changeMyText(QString)));

    chooseDateLabel = new QLabel("Choose date:", this);
    chooseDateLabel->move(10,60);

    editDate = new QDateEdit(this);
    editDate->setMaximumDate(QDate::currentDate());
    editDate->setMinimumDate(QDate(2020,1,22));
    editDate->move(200,60);

    dateLabel = new MyLabel(this);
    dateLabel->setFixedSize(300,20);
    dateLabel->move(100,100);

    connect(editDate,SIGNAL(dateChanged(QDate)),dateLabel,SLOT(changeMyText(QDate)));

    resize(400,200);
}

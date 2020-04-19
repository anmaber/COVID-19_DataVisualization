#include "basicanalysis.h"

BasicAnalysis::BasicAnalysis(QWidget *parent,std::unordered_map<std::string, int> countryIndex,
                             std::unordered_map<int,QDate> indexDate,std::vector<std::vector<int>> data)
    : QWidget(parent),
      data(data),
      indexDate(indexDate),
      countryIndex(countryIndex)
{
    for(auto c : countryIndex)
    {
        countries.append(c.first.c_str());
    }
    countries.sort();
    countries.removeFirst();
    countries.removeFirst();

    chooseCountryLabel = new QLabel(tr("Choose country/region: "),this);
    chooseCountryLabel->move(10,10);

    chooseCountryBox = new QComboBox(this);
    chooseCountryBox->addItems(countries);
    chooseCountryBox->move(200,10);

    chosenCountryLabel = new QLabel(tr("chosen country:"),this);
    chosenCountryLabel->move(10,40);

    chosenCountry = new QLabel(this);
    chosenCountry->move(200,40);
    chosenCountry->setFixedSize(300,20);

    connect(chooseCountryBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeVal()));

    chooseDateLabel = new QLabel("Choose date:", this);
    chooseDateLabel->move(10,60);

    editDate = new QDateEdit(this);
    editDate->setMaximumDate(QDate::currentDate().addDays(-1));
    editDate->setMinimumDate(QDate(2020,1,22));
    editDate->move(200,60);

    casesLabel = new QLabel(this);
    casesLabel->setFixedSize(300,20);
    casesLabel->move(100,100);

    connect(editDate,SIGNAL(dateChanged(QDate)),this,SLOT(changeVal()));

    resize(400,200);
}

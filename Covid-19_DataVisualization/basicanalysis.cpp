#include "basicanalysis.h"

int BasicAnalysis::getCountryIndex(const std::string &countryName, const std::unordered_map<std::string, int> &cimap)
{
    auto countryIter = cimap.find(countryName);
    if(countryIter != cimap.end()) return countryIter->second;
    return -1;
}

int BasicAnalysis::detDateIndex(const QDate &date, const std::unordered_map<int, QDate> &idmap)
{
    auto dateIter = std::find_if(idmap.begin(),idmap.end(),
                                 [&date](auto elem){return elem.second == date;});
    if(dateIter!=idmap.end()) return dateIter->first;
    return -1;
}

BasicAnalysis::BasicAnalysis(QWidget *parent, DataHolder* cases,
                             DataHolder* deaths, DataHolder* recoveries)
    : QWidget(parent),
      cases(cases),
      deaths(deaths),
      recoveries(recoveries)
{
    for(auto c : cases->getCountryIndexMap())
    {
        countries.append(c.first.c_str());
        qDebug() << c.first.c_str() << c.second;
    }
    countries.sort();
    //    countries.removeFirst();
    //    countries.removeFirst();

    chart = new QCustomPlot(this);
    chart->setObjectName("My chart");
    //chart->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    chart->setMinimumSize(500,500);
    chart->addGraph();
    chart->graph(0)->setPen(QPen(Qt::red));

    casesVisible = new QCheckBox("cases",this);
    deathsVisible  = new QCheckBox("deaths",this);
    recoveriesVisible  = new QCheckBox("recoveries",this);

    wybieranie = new QFormLayout();

    chooseCountryLabel = new QLabel(tr("Choose country/region: "),this);
    //chooseCountryLabel->move(10,10);

    chooseCountryBox = new QComboBox(this);
    chooseCountryBox->addItems(countries);
    //chooseCountryBox->move(200,10);
    wybieranie->addRow(chooseCountryLabel,chooseCountryBox);

    connect(chooseCountryBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeVal()));

    chooseDateLabel = new QLabel("Choose date:", this);
    //chooseDateLabel->move(10,60);

    editDate = new QDateEdit(this);
    editDate->setMaximumDate(QDate::currentDate().addDays(-1));
    editDate->setMinimumDate(QDate(2020,1,22));
    //editDate->move(200,60);
    wybieranie->addRow(chooseDateLabel,editDate);
    //setLayout(wybieranie);

    wybieranie->addWidget(casesVisible);
    wybieranie->addWidget(deathsVisible);
    wybieranie->addWidget(recoveriesVisible);

    zWykresem = new QHBoxLayout();
    zWykresem->addWidget(chart);
    zWykresem->addLayout(wybieranie);

    casesLabel = new QLabel("All cases:",this);
    //casesLabel->move(10,100);

    casesDisplay = new QLabel(this);
    //casesDisplay->move(200,100);
    casesDisplay->setFixedSize(100,20);

    casesAtDayLabel = new QLabel("Cases at chosen day:",this);
    //casesAtDayLabel->move(300, 100);
    casesAtDayDisplay = new QLabel(this);
    //casesAtDayDisplay->move(500,100);
    casesAtDayDisplay->setFixedSize(100,20);

    deathsLabel = new QLabel("All deaths:",this);
    //deathsLabel->move(10,140);

    deathsDisplay = new QLabel(this);
    //deathsDisplay->move(200,140);
    deathsDisplay->setFixedSize(100,20);

    deathsAtDayLabel = new QLabel("Deaths at chosen day:",this);
    //deathsAtDayLabel->move(300, 140);
    deathsAtDayDisplay = new QLabel(this);
    //deathsAtDayDisplay->move(500,140);
    deathsAtDayDisplay->setFixedSize(100,20);

    recoveriesLabel = new QLabel("All recoveries:",this);
    //recoveriesLabel->move(10,180);

    recoveriesDisplay = new QLabel(this);
    //recoveriesDisplay->move(200,180);
    recoveriesDisplay->setFixedSize(100,20);

    recoveriesAtDayLabel = new QLabel("Recoveries at chosen day:",this);
    //recoveriesAtDayLabel->move(300, 180);
    recoveriesAtDayDisplay = new QLabel(this);
    //recoveriesAtDayDisplay->move(500,180);
    recoveriesAtDayDisplay->setFixedSize(100,20);

    wszystkie = new QFormLayout();
    wszystkie->addRow(casesLabel,casesDisplay);
    wszystkie->addRow(deathsLabel,deathsDisplay);
    wszystkie->addRow(recoveriesLabel,recoveriesDisplay);
    //setLayout(wszystkie);

    aktywne = new QFormLayout();
    aktywne->addRow(casesAtDayLabel,casesAtDayDisplay);
    aktywne->addRow(deathsAtDayLabel,deathsAtDayDisplay);
    aktywne->addRow(recoveriesAtDayLabel,recoveriesAtDayDisplay);
    //setLayout(aktywne);

    wszystkieAktywne =new QHBoxLayout();
    wszystkieAktywne->addLayout(wszystkie);
    wszystkieAktywne->addLayout(aktywne);
    //setLayout(wszystkieAktywne);

    all = new QVBoxLayout();
    all->addLayout(zWykresem);
    all->addLayout(wszystkieAktywne);
    setLayout(all);

    connect(editDate,SIGNAL(dateChanged(QDate)),this,SLOT(changeVal()));

    resize(400,200);
}

void BasicAnalysis::changeVal()
{
    std::string countryName = chooseCountryBox->currentText().toStdString();
    QDate toSearch = editDate->date();

    int countryIndexCases = getCountryIndex(countryName, cases->getCountryIndexMap());
    int dateIndexCases = detDateIndex(toSearch,cases -> getIndexDateMap());
    int previousDay = dateIndexCases -1;
    if(countryIndexCases < 0 || dateIndexCases < 0)
    {
        casesDisplay->setText("-");
    }
    else
    {
        int currentCases = cases->getData().at(countryIndexCases).at(dateIndexCases);
        std::string c = std::to_string(currentCases);
        casesDisplay->setText(c.c_str());

        if(previousDay < 0)
        {
            casesAtDayDisplay->setText("-");
        }
        else
        {
            int casesAtDay = currentCases - cases->getData().at(countryIndexCases).at(previousDay);
            std::string c = std::to_string(casesAtDay);
            casesAtDayDisplay->setText(c.c_str());
        }
    }



    int countryIndexDeaths = getCountryIndex(countryName, deaths->getCountryIndexMap());
    int dateIndexDeaths = detDateIndex(toSearch,deaths -> getIndexDateMap());
    previousDay = dateIndexDeaths -1;
    if(countryIndexDeaths == -1 || dateIndexDeaths == -1)
    {
        deathsDisplay->setText("-");
    }
    else
    {
        int currentDeaths = deaths->getData().at(countryIndexDeaths).at(dateIndexDeaths);
        std::string c = std::to_string(currentDeaths);
        deathsDisplay->setText(c.c_str());

        if(previousDay < 0)
        {
            deathsAtDayDisplay->setText("-");
        }
        else
        {
            int deathsAtDay = currentDeaths - deaths->getData().at(countryIndexDeaths).at(previousDay);
            std::string c = std::to_string(deathsAtDay);
            deathsAtDayDisplay->setText(c.c_str());
        }
    }

    int countryIndexRecoveries = getCountryIndex(countryName, recoveries->getCountryIndexMap());
    int dateIndexRecoveries = detDateIndex(toSearch,recoveries -> getIndexDateMap());
    previousDay = dateIndexRecoveries -1;
    if(countryIndexRecoveries == -1 || dateIndexRecoveries == -1)
    {
        recoveriesDisplay->setText("-");
    }
    else
    {
        int currentRecoveries = recoveries->getData().at(countryIndexRecoveries).at(dateIndexRecoveries);
        std::string c = std::to_string(currentRecoveries);
        recoveriesDisplay->setText(c.c_str());

        if(previousDay < 0)
        {
            recoveriesAtDayDisplay->setText("-");
        }
        else
        {
            int recoveriesAtDay = currentRecoveries - recoveries->getData().at(countryIndexRecoveries).at(previousDay);
            std::string c = std::to_string(recoveriesAtDay);
            recoveriesAtDayDisplay->setText(c.c_str());
        }





    }

//    QVector<double> y(cases->getData().at(countryIndexCases).size());
//    for(auto i =0u; i< cases->getData().at(countryIndexCases).size();++i)
//    {
//        y[i]= cases->getData().at(countryIndexCases)[i];
//    }
//    for(auto i:y)
//    {
//        qDebug() << i;
//    }

//    QVector<double> x;
//    for(int i = 0; i< y.size();++i)
//    {
//        x.push_back(i);
//    }

//    //        for(auto i:x)
//    //        {
//    //            qDebug() << i;
//    //        }
//    //        QDate date = QDate(2020,1,22);
//    //        while(date != editDate->date())
//    //        {
//    //            x.push_back(date);
//    //            date.addDays(1);
//    //        }

//    chart->graph(0)->setData(x,y);
//    chart->graph(0)->rescaleAxes();


    //    std::string s = chooseCountryBox->currentText().toStdString();
    //    qDebug()<< s.c_str();
    //    auto cindex = cases->getCountryIndexMap().find(s);
    //    std::string str = cindex->first;
    //    qDebug() << str.c_str() << cindex->second;
    //    int ci = cindex->second;

    //    QDate toSearch = editDate->date();

    //    auto result = std::find_if(cases->getIndexDateMap().begin(),cases->getIndexDateMap().end(),
    //                               [&toSearch](auto elem){return elem.second == toSearch;});

    //    int di = result->first;
    //    qDebug() << "country index"<<ci;
    //    qDebug()<< "date index"<< di;
    //    int currentCases = cases->getData().at(ci).at(di);
    //    std::string c = std::to_string(currentCases);

    //    casesDisplay->setText(c.c_str());

}

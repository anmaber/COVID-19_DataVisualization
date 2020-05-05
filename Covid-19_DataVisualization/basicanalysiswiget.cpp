#include "basicanalysiswiget.h"
#include "ui_basicanalysiswiget.h"
#include <QDebug>
#include<QDateTime>
#include<QSharedPointer>

basicAnalysisWiget::basicAnalysisWiget(QWidget *parent,DataHolder* cases,
                                       DataHolder* deaths, DataHolder* recoveries) :
    QWidget(parent),
    ui(new Ui::basicAnalysisWiget),
    cases(cases),
    deaths(deaths),
    recoveries(recoveries)
{
    ui->setupUi(this);

    for(auto c : cases->getCountryIndexMap())
    {
        countries.append(c.first.c_str());
        //qDebug() << c.first.c_str() << c.second;
    }
    countries.sort();

    ui->comboBox->addItems(countries);
    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(-1));
}

basicAnalysisWiget::~basicAnalysisWiget()
{
    delete ui;
}

void basicAnalysisWiget::on_dateEdit_dateChanged(const QDate &date)
{
    setData(date,ui->comboBox->currentText());
}

void basicAnalysisWiget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    setData(ui->dateEdit->date(),arg1);
}


int basicAnalysisWiget::getCountryIndex(const QString &countryName, const std::unordered_map<std::string, int> &cimap)
{

    auto countryIter = cimap.find(countryName.toStdString());
    if(countryIter != cimap.end()) return countryIter->second;
    return -1;
}

int basicAnalysisWiget::getDateIndex(const QDate &date, const std::unordered_map<int, QDate> &idmap)
{
    auto dateIter = std::find_if(idmap.begin(),idmap.end(),
                                 [&date](auto elem){return elem.second == date;});
    if(dateIter!=idmap.end()) return dateIter->first;
    return -1;
}

void basicAnalysisWiget::setData(const QDate &date, const QString &country)
{

    int countryIndexCases = getCountryIndex(country, cases->getCountryIndexMap());
    int dateIndexCases = getDateIndex(date,cases -> getIndexDateMap());
    int previousDay = dateIndexCases -1;
    if(countryIndexCases < 0 || dateIndexCases < 0)
    {
        ui->Cases->setText("-");
    }
    else
    {
        int currentCases = cases->getData().at(countryIndexCases).at(dateIndexCases);
        std::string c = std::to_string(currentCases);
        ui->Cases->setText(c.c_str());

        if(previousDay < 0)
        {
            ui->CatDay->setText("-");
        }
        else
        {
            int casesAtDay = currentCases - cases->getData().at(countryIndexCases).at(previousDay);
            std::string c = std::to_string(casesAtDay);
            ui->CatDay->setText(c.c_str());
        }
    }

    int countryIndexDeaths = getCountryIndex(country, deaths->getCountryIndexMap());
    int dateIndexDeaths = getDateIndex(date,deaths -> getIndexDateMap());
    previousDay = dateIndexDeaths -1;
    if(countryIndexDeaths == -1 || dateIndexDeaths == -1)
    {
        ui->Deaths->setText("-");
    }
    else
    {
        int currentDeaths = deaths->getData().at(countryIndexDeaths).at(dateIndexDeaths);
        std::string c = std::to_string(currentDeaths);
        ui->Deaths->setText(c.c_str());

        if(previousDay < 0)
        {
            ui->DatDay->setText("-");
        }
        else
        {
            int deathsAtDay = currentDeaths - deaths->getData().at(countryIndexDeaths).at(previousDay);
            std::string c = std::to_string(deathsAtDay);
            ui->DatDay->setText(c.c_str());
        }
    }


    int countryIndexRecoveries = getCountryIndex(country, recoveries->getCountryIndexMap());
    int dateIndexRecoveries = getDateIndex(date,recoveries -> getIndexDateMap());
    previousDay = dateIndexRecoveries -1;
    if(countryIndexRecoveries == -1 || dateIndexRecoveries == -1)
    {
        ui->Recoveries->setText("-");
    }
    else
    {
        int currentRecoveries = recoveries->getData().at(countryIndexRecoveries).at(dateIndexRecoveries);
        std::string c = std::to_string(currentRecoveries);
        ui->Recoveries->setText(c.c_str());

        if(previousDay < 0)
        {
            ui->RatDay->setText("-");
        }
        else
        {
            int recoveriesAtDay = currentRecoveries - recoveries->getData().at(countryIndexRecoveries).at(previousDay);
            std::string c = std::to_string(recoveriesAtDay);
            ui->RatDay->setText(c.c_str());
        }

    }

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy");
    ui->chart->xAxis->setTicker(dateTicker);
    ui->chart->xAxis->setLabel("Date");
    ui->chart->yAxis->setLabel("Amount");
    QDateTime dateAxis= QDateTime(QDate(2020,1,22));
    QVector<QCPGraphData> timeData(dateIndexCases);
    for (int i=0; i<dateIndexCases; ++i)
    {
        timeData[i].key = dateAxis.addDays(i).toTime_t();
    }
    ui->chart->replot();


    ui->chart->addGraph();
    ui->chart->addGraph();
    ui->chart->addGraph();

    ui->chart->graph(0)->setPen(QPen(Qt::red));
    if(ui->checkBox->checkState() == Qt::Checked)
    {
        ui->chart->graph(0)->setVisible(true);

        for (int i=0; i<dateIndexCases; ++i)
        {
            timeData[i].value = cases->getData().at(countryIndexCases)[i];
        }

        ui->chart->graph(0)->data()->set(timeData);


        ui->chart->graph(0)->rescaleAxes();
        ui->chart->replot();
    }
    else
    {
        ui->chart->graph(0)->setVisible(false);
        ui->chart->replot();

    }


    if(ui->checkDeaths->checkState() == Qt::Checked)
    {
        ui->chart->graph(1)->setVisible(true);

        ui->chart->graph(1)->setPen(QPen(Qt::black));
        for (int i=0; i<dateIndexCases; ++i)
        {
            timeData[i].value = deaths->getData().at(countryIndexCases)[i];
        }

        ui->chart->graph(1)->data()->set(timeData);
        ui->chart->replot();
    }
    else
    {
        ui->chart->graph(1)->setVisible(false);
        ui->chart->replot();

    }
    if(ui->checkRecoveries->checkState() == Qt::Checked)
    {
        ui->chart->graph(2)->setVisible(true);

        ui->chart->graph(2)->setPen(QPen(Qt::green));
        for (int i=0; i<dateIndexCases; ++i)
        {
            timeData[i].value = recoveries->getData().at(countryIndexCases)[i];
        }

        ui->chart->graph(2)->data()->set(timeData);
        ui->chart->replot();
    }
    else
    {
        ui->chart->graph(2)->setVisible(false);
        ui->chart->replot();

    }

}

void basicAnalysisWiget::on_checkBox_clicked()
{
    setData(ui->dateEdit->date(),ui->comboBox->currentText());

}

void basicAnalysisWiget::on_checkRecoveries_clicked()
{
    setData(ui->dateEdit->date(),ui->comboBox->currentText());
}

void basicAnalysisWiget::on_checkDeaths_clicked()
{
    setData(ui->dateEdit->date(),ui->comboBox->currentText());
}

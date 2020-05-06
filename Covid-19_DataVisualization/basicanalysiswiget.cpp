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
    basicAnalysisWiget::setUpPlot();

    for(auto c : cases->getCountryIndexMap())
    {
        countries.append(c.first.c_str());
        //qDebug() << c.first.c_str() << c.second;
    }
    countries.sort();

    ui->comboBox->addItems(countries);
    ui->dateEditStart->setMaximumDate(ui->dateEdit->date());

    ui->dateEdit->setMaximumDate(QDate::currentDate().addDays(-1));
    ui->checkBox->setStyleSheet("QCheckBox::unchecked {color:black;font-weight:QFont::ExtraBold;} QCheckBox::checked {color:red;font-weight:bold;};");

}

basicAnalysisWiget::~basicAnalysisWiget()
{
    delete ui;
}

void basicAnalysisWiget::on_dateEdit_dateChanged(const QDate &date)
{
    if(date == QDate(2020,1,22))
    {
        ui->dateEditStart->setMaximumDate(date);
    }
    else
    {
        ui->dateEditStart->setMaximumDate(date.addDays(-1));
    }
    setData(date,ui->dateEditStart->date(),ui->comboBox->currentText());

}

void basicAnalysisWiget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    setData(ui->dateEdit->date(),ui->dateEditStart->date(),arg1);
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

void basicAnalysisWiget::setData(const QDate &date, const QDate&startDate, const QString &country)
{

    int countryIndexCases = getCountryIndex(country, cases->getCountryIndexMap());
    int dateIndexCases = getDateIndex(date,cases -> getIndexDateMap());
    int startDateIndex = getDateIndex(startDate,cases -> getIndexDateMap());
    int previousDay = dateIndexCases -1;
    if(countryIndexCases < 0 || dateIndexCases < 0)
    {
        ui->Cases->setText("-");
    }
    else
    {
        int currentCases = cases->getData().at(countryIndexCases).at(dateIndexCases);
        int casesBetweenDates = currentCases - cases->getData().at(countryIndexCases).at(startDateIndex);
        std::string c = std::to_string(casesBetweenDates);
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
        int deathsBetweenDates = currentDeaths - deaths->getData().at(countryIndexDeaths).at(startDateIndex);
        std::string c = std::to_string(deathsBetweenDates);
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
        int recoveriesBetweenDates = currentRecoveries - recoveries->getData().at(countryIndexRecoveries).at(startDateIndex);
        std::string c = std::to_string(recoveriesBetweenDates);
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

    qDebug()<< ui->chart->graphCount();
    QString titleText;
    titleText= "Covid-19 from " + startDate.toString("d.MM.yyyy")
            + " to "+ date.toString("d.MM.yyyy")
            + " in " + ui->comboBox->currentText();
    title->setText(titleText);
    QDateTime dateAxis= QDateTime(startDate);
    QVector<QCPGraphData> timeData(dateIndexCases - startDateIndex+1);
    for (int i=0; i<=dateIndexCases-startDateIndex; ++i)
    {
        qDebug() << "ok" <<i;
        timeData[i].key = dateAxis.addDays(i).toTime_t();
    }

    if(ui->checkBox->checkState() == Qt::Checked)
    {
        ui->chart->graph(0)->setVisible(true);

        for (int i=0; i<=dateIndexCases- startDateIndex; ++i)
        {
            qDebug() << "ok cases" <<i;

            timeData[i].value = cases->getData().at(countryIndexCases)[i+startDateIndex];
        }

        ui->chart->graph(0)->data()->set(timeData);
    }
    else
    {
        ui->chart->graph(0)->setVisible(false);
    }

    if(ui->checkDeaths->checkState() == Qt::Checked)
    {
        ui->chart->graph(1)->setVisible(true);
        for (int i=0; i<=dateIndexCases-startDateIndex; ++i)
        {
            qDebug() << "ok2" <<i;

            timeData[i].value = deaths->getData().at(countryIndexDeaths)[i+startDateIndex];
        }

        ui->chart->graph(1)->data()->set(timeData);
    }
    else
    {
        ui->chart->graph(1)->setVisible(false);
    }
    if(ui->checkRecoveries->checkState() == Qt::Checked)
    {
        ui->chart->graph(2)->setVisible(true);

        for (int i=0; i<=dateIndexCases-startDateIndex; ++i)
        {
            qDebug() << "ok3" <<i;

            timeData[i].value = recoveries->getData().at(countryIndexRecoveries)[i+startDateIndex];
        }

        ui->chart->graph(2)->data()->set(timeData);
    }
    else
    {
        ui->chart->graph(2)->setVisible(false);
    }

    ui->chart->rescaleAxes(true);
    ui->chart->replot();

}

//void basicAnalysisWiget::on_checkBox_clicked()
//{
//    ui->checkBox->setStyleSheet("QCheckBox { color: red }");
//    setData(ui->dateEdit->date(),ui->dateEditStart->date(),ui->comboBox->currentText());

//}

void basicAnalysisWiget::on_checkRecoveries_clicked()
{
    setData(ui->dateEdit->date(),ui->dateEditStart->date(),ui->comboBox->currentText());
}

void basicAnalysisWiget::on_checkDeaths_clicked()
{
    setData(ui->dateEdit->date(),ui->dateEditStart->date(),ui->comboBox->currentText());
}

void basicAnalysisWiget::on_dateEditStart_dateChanged(const QDate &startDate)
{
    setData(ui->dateEdit->date(),startDate,ui->comboBox->currentText());
}

void basicAnalysisWiget::on_checkBox_stateChanged(int state)
{

//    if(state == 0)
//    {
//        ui->checkBox->setFont();

//    }
//    else
//    {
//        ui->checkBox->setStyleSheet("QCheckBox { color: red }");
//    }
    setData(ui->dateEdit->date(),ui->dateEditStart->date(),ui->comboBox->currentText());

}

void basicAnalysisWiget::setUpPlot()
{
    ui->chart->addGraph();
    ui->chart->addGraph();
    ui->chart->addGraph();

    ui->chart->graph(0)->setPen(QPen(Qt::red));
    ui->chart->graph(1)->setPen(QPen(Qt::black));
    ui->chart->graph(2)->setPen(QPen(Qt::green));

    ui->chart->graph(0)->setName("Cases");
    ui->chart->graph(1)->setName("Deaths");
    ui->chart->graph(2)->setName("Recoveries");



    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd.MM.yyyy");
    ui->chart->xAxis->setTicker(dateTicker);
    ui->chart->xAxis->setLabel("Date");
    ui->chart->yAxis->setLabel("Amount");
    QDateTime dateAxis= QDateTime(QDate(2020,1,22));
    ui->chart->xAxis->setRange(dateAxis.toTime_t(),dateAxis.addDays(4).toTime_t());

    ui->chart->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    ui->chart->plotLayout()->insertRow(0);
    title = new QCPTextElement(ui->chart, "Covid-19", QFont("sans", 12, QFont::Bold));
    ui->chart->plotLayout()->addElement(0, 0, title);
    ui->chart->legend->setVisible(true);
    ui->chart->replot();
}

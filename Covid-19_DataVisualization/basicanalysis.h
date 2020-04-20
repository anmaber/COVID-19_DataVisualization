#ifndef BASICANALYSIS_H
#define BASICANALYSIS_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <vector>
#include <unordered_map>
#include <string>
#include <QStringList>
#include <algorithm>
#include "dataholder.h"
#include <QDebug>
/*
class MyLabel : public QLabel
{
public:
    MyLabel(QWidget *parent = nullptr) : QLabel(parent) {}
    Q_OBJECT

public slots:

    void changeMyText(const QString& str)
    {
      if(str == "Polska")
      {
          setText("Hurra");
      }
      else
      {
          setText("Buuuuuu");
      }
    }

    void changeMyText(const QDate& date)
    {
        setText(date.toString());
    }
};
*/
class BasicAnalysis : public QWidget
{
    Q_OBJECT

    QLabel *chooseCountryLabel;
    QComboBox *chooseCountryBox;
    QLabel *chosenCountryLabel;
    QLabel *chosenCountry;
    QLabel * chooseDateLabel;
    QDateEdit * editDate;
    QLabel * casesLabel;

    DataHolder*  cases;
    DataHolder * deaths;
    DataHolder * recoveries;

    QStringList countries;

public:
    explicit BasicAnalysis(QWidget *parent = nullptr, DataHolder* cases = nullptr,
                           DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);

signals:


public slots:
    void changeVal()
    {
        std::string s = chooseCountryBox->currentText().toStdString();
        qDebug()<< s.c_str();
        auto cindex = cases->getCountryIndexMap().find(s);
        std::string str = cindex->first;
        qDebug() << str.c_str() << cindex->second;
        int ci = cindex->second;

        QDate toSearch = editDate->date();

        auto result = std::find_if(cases->getIndexDateMap().begin(),cases->getIndexDateMap().end(),
                                   [&toSearch](auto elem){return elem.second == toSearch;});

        int di = result->first;
        qDebug() << "country index"<<ci;
        qDebug()<< "date index"<< di;
        int currentCases = cases->getData().at(ci).at(di);
        std::string c = std::to_string(currentCases);

        casesLabel->setText(c.c_str());
    }
};

#endif // BASICANALYSIS_H

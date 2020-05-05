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
#include <utility>
#include "dataholder.h"
#include <QDebug>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "qcustomplot.h"
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

    QFormLayout * wybieranie;
    QFormLayout * wszystkie;
    QFormLayout * aktywne;
    QHBoxLayout * wszystkieAktywne;
    QHBoxLayout * zWykresem;
    QVBoxLayout * all;

    QCustomPlot * chart;

    QLabel *chooseCountryLabel;
    QComboBox *chooseCountryBox;
    QLabel * chooseDateLabel;
    QDateEdit * editDate;
    QLabel * casesLabel;
    QLabel * casesDisplay;

    QLabel * casesAtDayLabel;
    QLabel * casesAtDayDisplay;

    QLabel* deathsLabel;
    QLabel* deathsDisplay;

    QLabel* deathsAtDayLabel;
    QLabel* deathsAtDayDisplay;

    QLabel* recoveriesLabel;
    QLabel* recoveriesDisplay;

    QLabel* recoveriesAtDayLabel;
    QLabel* recoveriesAtDayDisplay;

    DataHolder*  cases;
    DataHolder * deaths;
    DataHolder * recoveries;

    QStringList countries;

    int getCountryIndex(const std::string& countryName, const std::unordered_map<std::string, int>& cimap);
    int detDateIndex(const QDate& date, const std::unordered_map<int,QDate>& idmap);

//    void displayCases();
//    void displayDeaths();
//    void displayRecoveries();

public:
    explicit BasicAnalysis(QWidget *parent = nullptr, DataHolder* cases = nullptr,
                           DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);

signals:


public slots:
    void changeVal();

};

#endif // BASICANALYSIS_H

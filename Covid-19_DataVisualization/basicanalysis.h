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

    std::vector<std::vector<int>> data;
    std::unordered_map<int,QDate> indexDate;
    std::unordered_map<std::string, int> countryIndex;
    QStringList countries;

public:
    explicit BasicAnalysis(QWidget *parent = nullptr,std::unordered_map<std::string, int> countryIndex = {{"0",0}},
                           std::unordered_map<int,QDate> indexDate = {{0,QDate::currentDate()}},std::vector<std::vector<int>> data = {{0}});

signals:


public slots:
    void changeVal()
    {
        std::string s = chooseCountryBox->currentText().toStdString();
        auto cindex = countryIndex.find(s);
        QDate toSearch = editDate->date();

        auto result = std::find_if(indexDate.begin(),indexDate.end(),
                                   [&toSearch](auto elem){return elem.second == toSearch;});
        int ci = cindex->second;
        int di = result->first;

        int cases = data.at(ci).at(di);
        std::string c = std::to_string(cases);
        casesLabel->setText(c.c_str());
    }
};

#endif // BASICANALYSIS_H

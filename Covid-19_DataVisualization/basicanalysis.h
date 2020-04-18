#ifndef BASICANALYSIS_H
#define BASICANALYSIS_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>

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

class BasicAnalysis : public QWidget
{
    Q_OBJECT

    QLabel *chooseCountryLabel;
    QComboBox *chooseCountryBox;
    QLabel *chosenCountryLabel;
    MyLabel *chosenCountry;
    QLabel * chooseDateLabel;
    QDateEdit * editDate;
    MyLabel * dateLabel;



public:
    explicit BasicAnalysis(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // BASICANALYSIS_H

#ifndef BASICANALYSIS_H
#define BASICANALYSIS_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>

class BasicAnalysis : public QWidget
{
    Q_OBJECT

    QLabel *chooseCountryLabel;
    QComboBox *chooseCountryBox;
    QLabel *chosenCountryLabel;
    QLabel *chosenCountry;

public:
    explicit BasicAnalysis(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // BASICANALYSIS_H

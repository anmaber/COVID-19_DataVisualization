#ifndef BASICANALYSISWIGET_H
#define BASICANALYSISWIGET_H

#include <QWidget>
#include <QStringList>
#include "dataholder.h"

namespace Ui {
class basicAnalysisWiget;
}

class basicAnalysisWiget : public QWidget
{
    Q_OBJECT

public:
    explicit basicAnalysisWiget(QWidget *parent = 0,DataHolder* cases = nullptr,
                                DataHolder* deaths = nullptr, DataHolder * recoveries = nullptr);
    ~basicAnalysisWiget();

private slots:
    void on_dateEdit_dateChanged(const QDate &date);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_checkBox_clicked();

    void on_checkRecoveries_clicked();

    void on_checkDeaths_clicked();

private:
    Ui::basicAnalysisWiget *ui;
    DataHolder*  cases;
    DataHolder * deaths;
    DataHolder * recoveries;

    QStringList countries;

    void setData(const QDate& date, const QString& country);
    int getCountryIndex(const QString &countryName, const std::unordered_map<std::string, int> &cimap);
    int getDateIndex(const QDate &date, const std::unordered_map<int, QDate> &idmap);
};

#endif // BASICANALYSISWIGET_H

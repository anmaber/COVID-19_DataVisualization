#ifndef ANALYSISLAYOUT_H
#define ANALYSISLAYOUT_H

#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AnalysisLayout : public QWidget
{
    Q_OBJECT
    QFormLayout * wybieranie;
    QFormLayout * wszystkie;
    QFormLayout * aktywne;
    QHBoxLayout * wszystkieAktywne;
    QHBoxLayout * zWykresem;
    QVBoxLayout * all;

public:
    explicit AnalysisLayout(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // ANALYSISLAYOUT_H

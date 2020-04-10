#include <QtTest>

// add necessary includes here
#include "mainwindow.h"

class t1 : public QObject
{
    Q_OBJECT

public:
    t1();
    ~t1();

private slots:
    void test_case1();

};

t1::t1()
{

}

t1::~t1()
{

}

void t1::test_case1()
{

}

QTEST_APPLESS_MAIN(t1)

#include "tst_t1.moc"

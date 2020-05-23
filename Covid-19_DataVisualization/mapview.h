#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QObject>

class mapView : public QObject
{
    Q_OBJECT
public:
    explicit mapView(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MAPVIEW_H
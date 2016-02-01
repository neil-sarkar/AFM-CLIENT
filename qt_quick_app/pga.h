#ifndef PGA_H
#define PGA_H

#include <QObject>

class PGA : public QObject
{
    Q_OBJECT
public:
    explicit PGA(QObject *parent = 0);

signals:

public slots:
};

#endif // PGA_H
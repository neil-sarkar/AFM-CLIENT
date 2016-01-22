#ifndef AFM_H
#define AFM_H

#include <QObject>

class afm : public QObject
{
    Q_OBJECT
public:
    explicit afm(QObject *parent = 0);

signals:

public slots:
};

#endif // AFM_H
#ifndef DAC_H
#define DAC_H

#include <QObject>
#include <QtGlobal>
#include "command_node.h"

class DAC : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE set_value NOTIFY value_changed)
    Q_PROPERTY(int id READ id WRITE set_id NOTIFY id_changed)

public:
    explicit DAC(qint8 id, QObject *parent = 0);
    void set_value(double value);
    void set_id(qint8 id);
    double value();
    void init();
    qint8 id();
    Q_INVOKABLE void read();
    Q_INVOKABLE void write();

signals:
    void value_changed();
    void id_changed();

    void command_generated(CommandNode* c);

public slots:


private:
    qint8 m_id;
    double m_value;
};

#endif // DAC_H

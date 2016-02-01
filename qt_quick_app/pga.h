#ifndef PGA_H
#define PGA_H

#include <QObject>
#include "command_node.h"

class PGA : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE set_value NOTIFY value_changed)
public:
    explicit PGA(qint8 id);
    void set_value(double value);
    double value();

signals:
    void value_changed();
    void command_generated(CommandNode*);

public slots:

private:
    qint8 m_id;
    double m_value;
    void cmd_set_value();
    qint8 value_to_pga();

    struct Commands {
        const unsigned char Set = 0x54;
    } Commands;

};

#endif // PGA_H

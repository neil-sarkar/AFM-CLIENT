#ifndef ADC_H
#define ADC_H

#include <QObject>
#include "command_node.h"

class ADC : public QObject
{
    Q_OBJECT
public:
    explicit ADC(qint8 id, QObject *parent = 0);
    void read();

signals:
    void command_generated(CommandNode*);

public slots:

private:
    qint8 m_id;
    static constexpr double MAX_VOLTAGE = 2.5;
    static constexpr int RESOLUTION = 4095;
    static constexpr double SCALE_FACTOR = double(MAX_VOLTAGE)/RESOLUTION;
    static constexpr unsigned char READ_COMMAND = 0x63;
};

#endif // ADC_H

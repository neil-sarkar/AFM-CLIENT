#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H
#include <QObject>
#include <QtSerialPort>
class SerialPort: public QObject
{
  Q_OBJECT
  public:
    explicit SerialPort();
  signals:
    void connected();
    void disconnected();
  private:
    bool is_connected();
    QSerialPort port;
};
#endif // SERIAL_PORT_H

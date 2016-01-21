#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H
#include <QObject>
class SerialPort: public QObject
{
  Q_OBJECT
  public:
    explicit SerialPort();
  signals:
    void connected();
    void disconnected();
  private:
    bool is_connected;
};
#endif // SERIAL_PORT_H

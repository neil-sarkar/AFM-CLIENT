#ifndef RECEIVER_H
#define RECEIVER_H
#include <QObject>
class Receiver : public QObject
{
  Q_OBJECT
  public:
    explicit Receiver(QObject *parent = 0);
  signals:
    void sendToQml(int count);
  public slots:
    void receiveFromQml(int value);
    void receiveFromQml(double value);
    void receiveFromQml(QString message);
};

#endif // RECEIVER_H

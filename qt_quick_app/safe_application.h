#ifndef SAFEAPPLICATION_H
#define SAFEAPPLICATION_H
#include <QApplication>
#include <QObject>
#include <QEvent>

class SafeApplication : public QApplication
{
public:
    SafeApplication(int &argc, char *argv[]);
    bool notify(QObject *receiver_, QEvent *event_);
};

#endif // SAFEAPPLICATION_H

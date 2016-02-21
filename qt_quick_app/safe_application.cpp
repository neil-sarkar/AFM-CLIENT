#include "safe_application.h"
#include <QObject>
#include <QEvent>
#include <QDebug>

SafeApplication::SafeApplication(int &argc, char *argv[]) : QApplication(argc, argv) {

}

bool SafeApplication::notify(QObject *receiver_, QEvent *event_) {
    try {
        return QApplication::notify(receiver_, event_);
    } catch (std::exception &ex) {
        qDebug() << "std::exception was caught";
    }
    return false;
}

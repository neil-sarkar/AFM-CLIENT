#include "motor.h"
#include <QDebug>

Motor::Motor(QObject *parent) : QObject(parent)
{
    m_speed = 3;
}

void Motor::setRootObject(QQuickItem* root) {
    // disconnect from any previous root
//    if (root_ui_object != 0)
//        root_ui_object->disconnect(this);

    root_ui_object = root;

    if (root_ui_object) {
        // make connections
        connect(root_ui_object, SIGNAL(approach_clicked()), this, SLOT(run_motor()));
        connect(root_ui_object, SIGNAL(retract_clicked()), this, SLOT(run_motor()));
    }
}

void Motor::run_motor() {
    qDebug() << "lol\n";
}

double Motor::speed() {
    return m_speed;
}

void Motor::set_speed(double speed) {
    if (speed != m_speed) {
        m_speed = speed;
        qDebug() << "Changing speed to" << m_speed;
        emit speed_changed();
    }

}

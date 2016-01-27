import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: motor_controls

    signal approach_clicked()
    signal retract_clicked()

    Button {
        id: approach_button
        text: "Approach"
        onClicked: approach_clicked()
    }
    Button {
        id: retract_button
        text: "Retract"
        anchors.top: approach_button.bottom
        onClicked: retract_clicked()
    }
    SpinBox {
        id: motor_speed
        value: motor.speed
        minimumValue: 0
        maximumValue: 4
        stepSize: 1
        anchors.top: retract_button.bottom
    }
}

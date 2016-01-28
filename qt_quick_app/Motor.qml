import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: motor_controls

    MotorButton {
        id: approach_button
        text: "Approach"
        direction: 1
    }
    MotorButton {
        id: retract_button
        text: "Retract"
        direction: 0
        anchors.top: approach_button.bottom
    }
    SpinBox {
        id: motor_speed
        value: motor.speed
        minimumValue: 0
        maximumValue: 26300
        stepSize: 1
        anchors.top: retract_button.bottom
        onValueChanged: motor.speed = value;
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.4

Button {
    id: pressable_button
    property int direction: 1
    onClicked: {
        motor.direction = direction;
        motor.state = 1;
//        motor.single_step();
    }
//    Timer {
//        id: longPressTimer
//        interval: 1000
//        repeat: true
//        running: false
//    }
    onPressedChanged: {
        if (pressed) {
            motor.state = 1;
            motor.direction = direction
//            motor.run_continuous()
        } else {
            motor.state = 0;
        }
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.4

Button {
    id: pressable_button
    property int direction: 1
    onClicked: {
        motor.direction = direction;
        motor.state = 1;
        motor.single_step();
    }

//    Timer {
//        id: longPressTimer
//        interval: 1
//        repeat: true
//        running: false
//        onTriggered: motor.single_step()
//    }
//    onPressedChanged: {
//        if (pressed) {
//            motor.direction = direction;
//            motor.state = 1;
//            longPressTimer.running = true;
//        } else {
//            motor.state = 0;
//            longPressTimer.running = false;
//        }
//    }
}

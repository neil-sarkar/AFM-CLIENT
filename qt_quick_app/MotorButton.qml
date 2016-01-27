import QtQuick 2.0
import QtQuick.Controls 1.4

Button {
    id: pressable_button
    property int direction: 1
    Timer {
        id: longPressTimer
        interval: 1
        repeat: true
        running: false
        onTriggered: motor.run()
    }
    onPressedChanged: {
        if (pressed) {
            motor.direction = direction;
            motor.state = 1;
            longPressTimer.running = true;
        } else {
            motor.state = 0;
            longPressTimer.running = false;
        }
    }
}

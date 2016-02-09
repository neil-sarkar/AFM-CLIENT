import QtQuick 2.0
import QtQuick.Controls 1.4

Button {
    id: pressable_button
    property int direction: 1
    Timer {
        id: longPressTimer
        interval: 50
        repeat: false
        running: false
        onTriggered: {
            if (pressable_button.pressed) {
                motor.run_continuous()
            }
        }
    }
    onPressedChanged: {
        if (pressed) {
            motor.direction = direction;
            motor.state = 1;
            motor.cmd_single_step();
            longPressTimer.running = true;
        } else {
            motor.cmd_stop_continuous();
        }
    }
}

import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    Button {
        x: 0
        y: 75
        text: "start auto approach"
        id: start_auto_approach
        onClicked: approacher.cmd_start_auto_approach();
    }
    Button {
        x:0
        y: 125
        text: "stop auto approach"
        id: stop_auto_approach
        onClicked: approacher.cmd_stop_auto_approach();
    }
}

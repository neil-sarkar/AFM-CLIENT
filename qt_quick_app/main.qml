import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 400
    height:400
    id: window
    Motor{
        id: a
    }
    Sweep {
        id: sweep_area
        anchors.top: a.bottom
    }
    Button {
        x: 0
        y: 75
        text: "auto approach"
        id: auto_approach
        onClicked: afm.cmd_start_auto_approach();
    }
}

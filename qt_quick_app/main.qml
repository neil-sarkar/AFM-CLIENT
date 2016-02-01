import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    id: window
    Motor{
        id: a
    }
    DAC {
        anchors.top: a.bottom
        anchors.topMargin: 100;
    }
}

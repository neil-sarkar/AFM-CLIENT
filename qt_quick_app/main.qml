import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1000
    id: window
    Motor{
        id: a
    }
    DAC {
        id: dac_area
        anchors.top: a.bottom
        anchors.topMargin: 100;
    }
    Button {
        anchors.top: dac_area.bottom
        text: "Start frequency sweep"
        onClicked: afm.frequency_sweep();
    }
}

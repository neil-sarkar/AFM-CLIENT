import QtQuick 2.0

Item {
    Text {
        id: start
        text: "start frequency: " + dds.start_frequency
    }
    Text {
        id: end
        text: "end frequency: " + dds.end_frequency
        anchors.top: start.bottom
    }
    Text {
        text: "step size: " + dds.step_size
        anchors.top: end.bottom
    }
}

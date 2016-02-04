import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: item
    height: 100
    width: 100
    Button {
        id: start_button
        text: "Start Sweep"
        onClicked: afm.frequency_sweep();
    }
    Text {
        id: label1
        text: "Start Frequency"
        anchors.top: start_frequency.top
    }
    SpinBox {
        id: start_frequency
        anchors.top: start_button.bottom
        anchors.left: label1.right
        value: dds.start_frequency
        onValueChanged: dds.start_frequency = value;
        minimumValue: 0
        maximumValue: 15000
    }
    Text {
        id: label2
        text: "End Frequency"
        anchors.top: end_frequency.top
    }
    SpinBox {
        id: end_frequency
        anchors.top: start_frequency.bottom
        anchors.left: label2.right
        value: dds.end_frequency
        onValueChanged: dds.end_frequency = value;
        minimumValue: start_frequency.value
        maximumValue: 15000
    }
    Text {
        id: label3
        text: "Step Size"
        anchors.top: step_size.top
    }
    SpinBox {
        id: step_size
        anchors.top: end_frequency.bottom
        anchors.left: label3.right
        value: dds.step_size
        onValueChanged: dds.step_size = value;
        minimumValue: 1
        maximumValue: 1000
    }

}

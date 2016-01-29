import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    Button {
        id: serial_close
        text: "Close port"
        onClicked: serial_port.close()
        anchors.top: read_dac_button.bottom
    }

    Button {
        id: init_dac
        text: "Init DAC"
        onClicked: dac.init()
        anchors.top: serial_close.bottom
    }
    SpinBox {
        id: dac_value
        value: dac.value
        minimumValue: 0
        maximumValue: 3.3
        stepSize: 0.1
        decimals: 1
        onValueChanged: dac.value = value;
    }
    SpinBox {
        id: dac_id
        value: dac.id
        minimumValue: 0
        maximumValue: 11
        stepSize: 1
        onValueChanged: dac.id = value;
        anchors.left: dac_value.right
    }
    Button {
        id: read_dac_button
        text: "Read DAC value"
        anchors.top: dac_value.bottom
        onClicked: dac.read()
    }
}

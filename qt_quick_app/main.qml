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
    Approach {
    }
    Button {
        id: scan
        y: 325
        text: "Scan"
        onClicked: scanner.start_state_machine();
    }
    Button {
        y: 250
        text: "read adc"
        onClicked: adc.read();
    }
    Text {
        y:225
        text: "ADC Z Piezo: " + ((adc.value /4095) * 2.5);
    }
    SpinBox {
        id: coarse_z
        y: 275
//        value: dac_z_coarse.value
        onValueChanged: dac_z_coarse.value = value;
        decimals: 4
    }
    Button {
        y: 275
        anchors.left: coarse_z.right
        text: "Read Coarse Z"
        onClicked: dac_z_coarse.cmd_read_value();
    }
    SpinBox {
        y: 300
//        value: dac_z_fine.value
        onValueChanged: dac_z_fine.value = value;
        decimals: 4

    }
    Button {
        y: 300
        anchors.left: coarse_z.right
        text: "Read Fine Z"
        onClicked: dac_z_fine.cmd_read_value();
    }
    PID {
        x: 200
    }
    DDS {
        x: 200
        y: 200
    }
    PGA {
        x:200
        y:250
    }
    Button {
        id: force_curve
        text: "gen curve"
        y:350
        onClicked: afm.cmd_generate_force_curve();
    }

}

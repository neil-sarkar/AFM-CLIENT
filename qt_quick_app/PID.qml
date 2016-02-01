import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    Text {
        id: p_label
        text: "Proportional"
        lineHeight: 2
    }
    SpinBox {
        value: pid.proportional
        anchors.left: p_label.right
        onValueChanged: pid.proportional = value
    }
    Text {
        id: i_label
        text: "Integral"
        anchors.top: p_label.bottom
        lineHeight: 2
    }
    SpinBox {
        value: pid.integral
        anchors.left: i_label.right
        anchors.top: p_label.bottom
        onValueChanged: pid.integral = value
    }
    Text {
        id: d_label
        text: "Derivative"
        anchors.top: i_label.bottom
        lineHeight: 2
    }
    SpinBox {
        value: pid.derivative
        anchors.left: d_label.right
        anchors.top: i_label.bottom
        onValueChanged: pid.derivative = value
    }
    Button {
        id: pid_enable
        anchors.top: d_label.bottom
        text: "On"
        onClicked: {
            pid.set_enabled();
        }
    }
    Button {
        id: pid_disable
        text: "Off"
        anchors.top: d_label.bottom
        anchors.left: pid_enable.right
        onClicked: {
            pid.set_disabled();
        }
    }
    Text {
        id: status
        anchors.top: pid_disable.bottom
        text: pid.enabled
    }
}

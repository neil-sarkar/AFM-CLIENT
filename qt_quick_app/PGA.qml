import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    SpinBox {
        id: pga_value
        value: pga.value
        minimumValue: 0
        stepSize: 0.1
        decimals: 1
        onValueChanged: pga.value = value;
    }
}

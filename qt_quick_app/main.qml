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
}

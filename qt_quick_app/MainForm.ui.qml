import QtQuick 2.5

Rectangle {
    property alias mouseArea: mouseArea

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        PGA {
            id: pGA1
            x: 94
            y: 156
        }
    }

    Text {
        anchors.centerIn: parent
        text: "Hello World"
    }
}

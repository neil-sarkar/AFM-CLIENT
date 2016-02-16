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

        Column {
            id: column2
            x: 179
            y: 0
            width: 181
            height: 360
        }

        Image {
            id: image1
            x: 9
            y: 70
            width: 170
            height: 189
            source: "afm.jpeg"
        }
    }

    Text {
        anchors.centerIn: parent
        text: "Welcome to icspi"
        anchors.verticalCenterOffset: -52
        anchors.horizontalCenterOffset: 90
    }

    Column {
        id: column1
        x: 0
        y: 0
        width: 180
        height: 360
    }
}

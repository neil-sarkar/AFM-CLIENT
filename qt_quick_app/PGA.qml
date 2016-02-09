import QtQuick 2.0

Item {
    Text {
        id: a
        text: "x1:" + pga_x1.value
    }
    Text {
        id: b
        text: "x2:" + pga_x2.value
        anchors.top: a.bottom
    }
    Text {
        id: c
        text: "y1:" + pga_y1.value
        anchors.top: b.bottom
    }
    Text {
        id: d
        text: "y2:" + pga_y2.value
        anchors.top: c.bottom
    }
    Text {
        id: e
        text: "zf:" + pga_z_fine.value
        anchors.top: d.bottom
    }
    Text {
        id: f
        text: "zc:" + pga_z_coarse.value
        anchors.top: e.bottom
    }
    Text {
        id: g
        text: "dds:" + pga_dds.value
        anchors.top: f.bottom
    }
    Text {
        id: h
        text: "leveling:" + pga_leveling.value
        anchors.top: g.bottom
    }

}

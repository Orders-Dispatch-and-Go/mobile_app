import QtQuick 2.15
import QtLocation 6.5
import QtPositioning 6.5

import org.kde.kirigami 2.20 as Kirigami

MapQuickItem {
    id: root
    visible: true

    property int markerSize: 28
    property Map map

    property int index

    signal clicked(int id)

    width: markerSize
    height: markerSize

    anchorPoint.x: width / 2
    anchorPoint.y: height

    sourceItem: Rectangle {
        width: root.markerSize
        height: root.markerSize
        radius: root.markerSize / 2
        color: Kirigami.Theme.backgroundColor
        border.color: Kirigami.Theme.textColor
        border.width: 2
        Text {
            anchors.fill: parent
            anchors.margins: 3
            text: (root.index + 1).toString()
            color: Kirigami.Theme.textColor
            font.pointSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked(root.index)
    }
}

import QtQuick 2.15
import QtLocation 6.5
import QtPositioning 6.5

MapQuickItem {
    id: root
    visible: true

    property color markerColor: "red"
    property int markerSize: 28
    property Map map

    width: markerSize
    height: markerSize

    anchorPoint.x: width / 2
    anchorPoint.y: height

    sourceItem: Rectangle {
        width: root.markerSize
        height: root.markerSize
        radius: root.markerSize / 2
        color: root.markerColor
        border.color: "#00000080"
        border.width: 2
    }

    MouseArea {
        anchors.fill: parent
        drag.target: parent
        cursorShape: Qt.OpenHandCursor

        onPressed: cursorShape = Qt.ClosedHandCursor
        onReleased: cursorShape = Qt.OpenHandCursor
    }
}

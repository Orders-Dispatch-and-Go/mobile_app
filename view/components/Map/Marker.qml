import QtQuick 2.15
import QtLocation 6.5
import QtPositioning 6.5
import org.kde.kirigami 2.20 as Kirigami

MapQuickItem {
    id: root
    visible: true

    property color markerColor: "red"
    property int markerSize: 28
    property Map map

    // ОБЯЗАТЕЛЬНО! Иначе MapQuickItem может не отображаться
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

    // Drag & Drop
    MouseArea {
        anchors.fill: parent
        drag.target: parent
        cursorShape: Qt.OpenHandCursor

        onPressed: cursorShape = Qt.ClosedHandCursor
        onReleased: cursorShape = Qt.OpenHandCursor

        onPositionChanged: {
            const localPoint = Qt.point(parent.x + parent.width / 2, parent.y + parent.height);
            parent.coordinate = root.map.toCoordinate(localPoint);
        }
    }
}

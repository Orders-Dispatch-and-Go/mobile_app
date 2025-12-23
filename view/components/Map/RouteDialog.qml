import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtLocation 6.5
import QtPositioning 6.5
import org.kde.kirigami 2.20 as Kirigami

import untitled

Kirigami.Dialog {
    id: root
    modal: true
    title: "Выбор точки"

    standardButtons: Kirigami.Dialog.Ok | Kirigami.Dialog.Cancel

    property var startCoord: QtPositioning.coordinate(54.847297, 83.092242)
    property var finishCoord: QtPositioning.coordinate(54.848820, 83.092405) // Москва

    contentItem: Map {
        id: map

        property var focusCoord: QtPositioning.coordinate(54.847297, 83.092242) // positionSource.position.coordinate
        property alias marker1: marker1
        property alias marker2: marker2
        property bool panEnabled: false

        PositionSource {
            id: positionSource
            active: true
            updateInterval: 1000

            onPositionChanged: {
                if (position.coordinate.isValid) {
                    map.focusCoord = position.coordinate;
                }
            }
        }
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing
        zoomLevel: 14
        plugin: Plugin {
            name: "osm"
            PluginParameter {
                name: "osm.mapping.cache.size"
                value: 256 * 1024 * 1024
            }
        }

        Marker {
            id: marker1
            map: map
        }
        Marker {
            id: marker2
            map: map
        }

        center: map.focusCoord

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            property real lastX: -1
            property real lastY: -1

            onPositionChanged: mouse => {
                if (!map.panEnabled)
                    return;
                const dx = mouse.x - lastX;
                const dy = mouse.y - lastY;
                map.pan(-dx, -dy);
                lastX = mouse.x;
                lastY = mouse.y;
            }
            onClicked: mouse => {
                lastX = mouse.x;
                lastY = mouse.y;
                map.panEnabled = true;
                mouse.accepted = true;
            }
            onReleased: mouse => {
                lastX = -1;
                lastY = -1;
                map.panEnabled = false;
            }
        }

        Marker {
            id: markerStart
            text: "начало"
            coordinate: root.startCoord
            markerColor: Kirigami.Theme.backgroundColor
        }
        Marker {
            id: markerFinish
            text: "конец"
            coordinate: root.finishCoord
            markerColor: Kirigami.Theme.positiveBackgroundColor
        }

        ZoomButton {
            id: zoomIn
            anchors.margins: Kirigami.Units.largeSpacing
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            text: "+"
            zoomAction: () => {
                map.zoomLevel += 1;
            }
        }
        ZoomButton {
            id: zoomOut
            anchors.margins: Kirigami.Units.largeSpacing
            anchors.bottom: zoomIn.top
            anchors.left: parent.left
            text: "-"
            zoomAction: () => {
                map.zoomLevel -= 1;
            }
        }
    }
}

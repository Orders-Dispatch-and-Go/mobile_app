import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtLocation 6.5
import QtPositioning 6.5
import org.kde.kirigami 2.20 as Kirigami

import untitled

Kirigami.Page {
    id: root
    title: qsTr("Route")

    /* Пример списка точек */
    property var waypoints: [
        {
            point: QtPositioning.coordinate(55.751244, 37.618423)
        },
        {
            point: QtPositioning.coordinate(55.760000, 37.620000)
        },
        {
            point: QtPositioning.coordinate(55.755500, 37.630000)
        }
    ]

    Map {
        id: map
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing

        property var focusCoord: QtPositioning.coordinate(55.751244, 37.618423)
        property bool panEnabled: false
        zoomLevel: 14
        center: map.focusCoord

        plugin: Plugin {
            name: "osm"
            PluginParameter {
                name: "osm.mapping.cache.size"
                value: 256 * 1024 * 1024
            }
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            property real lastX: -1
            property real lastY: -1

            onPositionChanged: mouse => {
                if (!map.panEnabled)
                    return;
                map.pan(-(mouse.x - lastX), -(mouse.y - lastY));
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

        /* Repeater для WayPoint */
        Repeater {
            model: root.waypoints
            delegate: WayPoint {
                index: model.index
                coordinate: modelData.point
                onClicked: index => {
                    console.log("clicked = ", index);
                }
                Component.onCompleted: {
                    console.log("model = ", model);
                }
            }
        }

        ZoomButton {
            id: zoomIn
            anchors.margins: Kirigami.Units.largeSpacing
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            text: "+"
            zoomAction: () => map.zoomLevel += 1
        }
        ZoomButton {
            id: zoomOut
            anchors.margins: Kirigami.Units.largeSpacing
            anchors.bottom: zoomIn.top
            anchors.left: parent.left
            text: "-"
            zoomAction: () => map.zoomLevel -= 1
        }
    }
}

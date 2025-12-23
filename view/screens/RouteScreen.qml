import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtLocation 6.5
import QtPositioning 6.5
import org.kde.kirigami 2.20 as Kirigami

import untitled

Kirigami.Page {
    id: root
    title: qsTr("Поездка")

    /* Пример списка точек */
    property var waypoints: backend.waypoints
    property var routePath: waypoints.map(p => QtPositioning.coordinate(p.x, p.y))
    property var stops: backend.stops

    property int selectedStop: -1

    Component.onCompleted: {
        if (routePath.length > 0) {
            map.center = routePath[0];
        }
    }

    Map {
        id: map
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing

        property var focusCoord: QtPositioning.coordinate(waypoints[0].x, waypoints[0].y)
        property bool panEnabled: false
        zoomLevel: 14
        center: map.focusCoord

        MapPolyline {
            line.width: 5
            line.color: Kirigami.Theme.highlightColor
            path: root.routePath
            smooth: true
        }

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

        Repeater {
            model: root.stops
            delegate: WayPoint {
                index: model.index
                coordinate: QtPositioning.coordinate(modelData.fromStation.coords.lat, modelData.fromStation.coords.lon)
                borderColor: "black"
            }
        }
        Repeater {
            model: root.stops
            delegate: WayPoint {
                index: model.index
                color: backend.finished ? Kirigami.Theme.positiveTextColor : Kirigami.Theme.negativeTextColor
                borderColor: "black"
                coordinate: QtPositioning.coordinate(modelData.toStation.coords.lat, modelData.toStation.coords.lon)
                onClicked: index => {
                    root.selectedStop = index;
                    orderDialog.open(); // TODO: передать dto
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
    OrderDialog {
        id: orderDialog
        visible: false
        width: parent.width
        height: parent.height

        x: root.x
        y: root.y + root.height - height
        dto: root.selectedStop >= 0 ? root.stops[root.selectedStop] : null
        onComplete: {
            console.log("onComplete");
            finishOrderDialog.open();
        }
        onCancel: {
            console.log("onCanceled");
            backend.cancelOrder(root.selectedStop);
        }
    }
    FinishOrderDialog {
        id: finishOrderDialog
        visible: false
        width: parent.width
        height: parent.height

        dto: root.selectedStop >= 0 ? root.stops[root.selectedStop] : null
        index: root.selectedStop
    }
}

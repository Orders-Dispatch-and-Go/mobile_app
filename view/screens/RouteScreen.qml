import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 6.5
import QtPositioning 6.5
import org.kde.kirigami 2.20 as Kirigami

import untitled

Kirigami.Page {
    id: page
    title: "Выбор точки"

    property var selectedCoordinate: QtPositioning.coordinate(55.751244, 37.618423) // Москва
    property var startCoord: QtPositioning.coordinate(55.751230, 37.618423) // Москва
    property var finishCoord: QtPositioning.coordinate(55.751250, 37.618423) // Москва

    Map {
        id: map

        property Marker marker1
        property Marker marker2

        anchors.fill: parent
        zoomLevel: 14
        plugin: Plugin {
            name: "osm"

            // Можно явно разрешить кэш:
            PluginParameter {
                name: "osm.mapping.cache.size"
                value: 256 * 1024 * 1024
            } // 256 MB
        }

        center: selectedCoordinate

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked: mouse => {
                console.log(mouse.x, mouse.y);
                const coord = map.toCoordinate(Qt.point(mouse.x, mouse.y));
            }
        }

        Marker {
            id: markerStart
            coordinate: page.startCoord
            markerColor: "green"
        }
        Marker {
            id: markerFinish
            coordinate: page.finishCoord
            markerColor: "red"
        }
    }
}

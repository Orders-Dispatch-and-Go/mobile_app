import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org.kde.kirigami as Kirigami

ColumnLayout {
    id: root

    property var dto

    property int accuracy: 3

    ColumnLayout {
        Layout.fillWidth: true
        RouteHighlight {
            Layout.fillWidth: true
            height: 100
            point: {
                "address": dto.fromStation.address,
                "lat": dto.fromStation.coords.lat.toFixed(accuracy),
                "lon": dto.fromStation.coords.lon.toFixed(accuracy)
            }
        }
        RouteHighlight {
            Layout.fillWidth: true
            height: 100
            point: {
                "address": dto.toStation.address,
                "lat": dto.toStation.coords.lat.toFixed(accuracy),
                "lon": dto.toStation.coords.lon.toFixed(accuracy)
            }
        }
    }
    RowLayout {
        Layout.fillWidth: true
        ColumnLayout {
            Layout.fillHeight: true
            Item {
                Layout.fillHeight: true
            }
            Kirigami.Heading {
                text: qsTr("Вознаграждение") + ": " + (dto.price || 0) + " ₽"
                level: 3
                wrapMode: Text.WordWrap
            }
            Kirigami.Heading {
                visible: dto.worth !== undefined
                enabled: dto.worth !== undefined
                text: qsTr("Стоимость") + ": " + (dto.cost || 0) + " ₽"
                level: 4
                wrapMode: Text.WordWrap
            }
            Kirigami.Heading {
                visible: dto.weight !== undefined
                enabled: dto.weight !== undefined
                text: qsTr("Вес") + ": " + (dto.weight || 0) + " kg"
                level: 4
                wrapMode: Text.WordWrap
            }
            Item {
                Layout.fillHeight: true
            }
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        ShowSizes {
            boxWidth: dto.width
            boxHeight: dto.height
            boxDepth: dto.length
            strokeColor: Kirigami.Theme.textColor
            fillColor: Kirigami.Theme.backgroundColor
            textColor: Kirigami.Theme.textColor
        }
    }
    Item {
        height: 30
        Layout.fillWidth: true
    }
}

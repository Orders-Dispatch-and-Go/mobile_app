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
            point: {
                "address": dto.start.address,
                "lat": dto.start.coords.lat.toFixed(accuracy),
                "lon": dto.start.coords.lon.toFixed(accuracy)
            }
        }
        RouteHighlight {
            point: {
                "address": dto.finish.address,
                "lat": dto.finish.coords.lat.toFixed(accuracy),
                "lon": dto.finish.coords.lon.toFixed(accuracy)
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
                text: qsTr("price") + ": " + (dto.price || 0) + " ₽"
                level: 1
                wrapMode: Text.WordWrap
            }
            Kirigami.Heading {
                visible: dto.cost !== undefined
                enabled: dto.cost !== undefined
                text: qsTr("worth") + ": " + (dto.cost || 0) + " ₽"
                level: 3
                wrapMode: Text.WordWrap
            }
            Kirigami.Heading {
                visible: dto.weight !== undefined
                enabled: dto.weight !== undefined
                text: qsTr("weight") + ": " + (dto.weight || 0) + " kg"
                level: 3
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

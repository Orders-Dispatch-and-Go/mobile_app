import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org.kde.kirigami as Kirigami

ColumnLayout {
    id: root

    property var dto

    property int accuracy: 3

    RouteHighlight {
        Layout.fillWidth: true
        pointA: {
            "lat": dto.start.coords.lat.toFixed(accuracy),
            "lon": dto.start.coords.lon.toFixed(accuracy)
        }
        pointB: {
            "lat": dto.finish.coords.lat.toFixed(accuracy),
            "lon": dto.finish.coords.lon.toFixed(accuracy)
        }
    }
    RowLayout {
        Layout.fillWidth: true
        ColumnLayout {
            Kirigami.Heading {
                text: qsTr("price") + ": " + (dto.price || 0) + " ₽"
                level: 1
                wrapMode: Text.WordWrap
            }
            Kirigami.Heading {
                text: qsTr("worth") + ": " + (dto.cost || 0) + " ₽"
                level: 3
                wrapMode: Text.WordWrap
            }
            Kirigami.Heading {
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

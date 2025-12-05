import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org.kde.kirigami as Kirigami

ColumnLayout {
    id: root

    property var dto

    RouteHighlight {
        Layout.fillWidth: true
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
            boxWidth: dto.width || 20
            boxHeight: dto.height || 30
            boxDepth: dto.depth || 40
            strokeColor: Kirigami.Theme.textColor
            fillColor: Kirigami.Theme.backgroundColor
            textColor: Kirigami.Theme.textColor
        }
    }
    Item {
        height: 40
        Layout.fillWidth: true
    }
}

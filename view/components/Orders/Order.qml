import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import org.kde.kirigami as Kirigami

Kirigami.Card {
    id: root

    width: 500

    // Отключаем стандартный контейнер actions
    actions: []
    property var dto: null

    footer: RowLayout {
        Layout.fillWidth: true
        Item {
            Layout.fillWidth: true
        }
        RowLayout {
            Button {
                text: qsTr("reject")
                icon.name: "dialog-cancel"
            }
            Button {
                text: qsTr("accept")
                icon.name: "dialog-ok"
            }
        }
    }

    header: Kirigami.Heading {
        text: qsTr("Order #" + dto.id)
        level: 2
    }

    contentItem: ColumnLayout {
        id: body
        anchors.fill: parent
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
}

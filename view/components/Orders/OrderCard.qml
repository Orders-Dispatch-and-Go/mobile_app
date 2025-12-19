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
    signal accepted

    footer: RowLayout {
        Layout.fillWidth: true
        Item {
            Layout.fillWidth: true
        }
        RowLayout {
            Button {
                text: qsTr("reject")
                icon.name: "dialog-cancel"
                onClicked: {
                    root.visible = false;
                    root.width = 0;
                    root.height = 0;
                }
            }
            Button {
                text: qsTr("accept")
                icon.name: "dialog-ok"
                onClicked: {
                    root.visible = false;
                    root.width = 0;
                    root.height = 0;
                    root.accepted;
                }
            }
        }
    }

    header: Kirigami.Heading {
        text: root.getHeader()
        level: 2
    }

    contentItem: Order {
        dto: root.dto
    }

    function getHeader() {
        return "#" + ("" + dto.uuid).split("-")[1];
    }
}

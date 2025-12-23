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
    property var onAccepted: () => {}
    property var onRejected: () => {}

    footer: RowLayout {
        Layout.fillWidth: true
        Item {
            Layout.fillWidth: true
        }
        RowLayout {
            Button {
                text: qsTr("Отклонить")
                icon.name: "dialog-cancel"
                onClicked: root.onRejected()
            }
            Button {
                text: qsTr("Принять")
                icon.name: "dialog-ok"
                onClicked: root.onAccepted()
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

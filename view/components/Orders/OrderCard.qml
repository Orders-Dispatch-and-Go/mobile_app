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

    contentItem: Order {
        dto: root.dto
    }
}

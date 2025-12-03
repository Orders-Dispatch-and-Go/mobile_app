import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Kirigami.ScrollablePage {
    id: root
    title: qsTr("Start new route")
    ColumnLayout {
        height: parent.height
        Filter {
            id: order
            Layout.fillWidth: true
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Button {
            Layout.fillWidth: true
            text: "find orders"
            onClicked: {
                backend.startRoute(order.address, order.latitude, order.longitude);
            }
        }
    }
}

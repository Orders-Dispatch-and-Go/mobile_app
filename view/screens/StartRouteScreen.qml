import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Kirigami.Page {
    id: root
    title: qsTr("Start new route")

    ColumnLayout {
        width: parent.width
        height: parent.height
        Button {
            text: qsTr("Start")
            onClicked: {}
        }
    }
}

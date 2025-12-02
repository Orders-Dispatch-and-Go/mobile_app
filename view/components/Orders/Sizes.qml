import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Item {
    id: root

    property alias used: checkBox.checked
    property alias width: width.value
    property alias height: height.value
    property alias depth: depth.value

    CheckBox {
        id: checkBox
        text: qsTr("Use Dimensions")
        checked: true
    }

    ColumnLayout {
        visible: checkBox.checked
        height: checkBox.checked ? Kirigami.Units.gridUnit * 10 : 0
        Dimension {
            id: width
            Layout.fillWidth: true
            title: qsTr("Width")
        }
        Dimension {
            id: height
            Layout.fillWidth: true
            title: qsTr("Height")
        }
        Dimension {
            id: depth
            Layout.fillWidth: true
            title: qsTr("Depth")
        }
    }
}

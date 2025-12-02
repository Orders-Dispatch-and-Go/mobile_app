import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

ColumnLayout {
    id: root

    height: Math.min(400, implicitHeight)

    property alias used: checkBox.checked
    property alias dimWidth: widthDim.value
    property alias dimHeight: heightDim.value
    property alias dimDepth: depthDim.value

    CheckBox {
        id: checkBox
        text: qsTr("Use Dimensions")
        checked: true
        Layout.fillWidth: true
    }
    ColumnLayout {
        enabled: checkBox.checked
        Layout.fillWidth: true
        Dimension {
            id: widthDim
            Layout.fillWidth: true
            title: qsTr("Width")
        }
        Dimension {
            id: heightDim
            Layout.fillWidth: true
            title: qsTr("Height")
        }
        Dimension {
            id: depthDim
            Layout.fillWidth: true
            title: qsTr("Depth")
        }
    }
}

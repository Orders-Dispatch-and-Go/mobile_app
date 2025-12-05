import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

ColumnLayout {
    id: root

    property alias used: checkBox.checked
    property alias value: textField.text

    CheckBox {
        id: checkBox
        text: qsTr("Use date")
    }

    RowLayout {
        enabled: checkBox.checked
        Layout.fillWidth: true

        Label {
            text: qsTr("Date")
        }
        Item {
            Layout.fillWidth: true
        }
        TextField {
            id: textField
            placeholderText: "01.01.2025"
            inputMask: "99.99.9999"
        }
    }
}

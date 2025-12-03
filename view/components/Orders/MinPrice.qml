import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

ColumnLayout {
    id: root
    property alias used: checkBox.checked
    property alias value: spin.value
    signal priceChanged(real price)

    height: Math.min(100, implicitHeight)

    CheckBox {
        id: checkBox
        text: qsTr("Set minimum price")
        checked: true
        Layout.fillWidth: true
    }
    ColumnLayout {
        enabled: checkBox.checked
        Layout.fillWidth: true
        RowLayout {
            Label {
                text: qsTr("price: ")
            }
            Item {
                Layout.fillWidth: true
            }
            SpinBox {
                id: spin
                from: 1
                to: 999999999
                stepSize: 1
                editable: true
                value: 10

                textFromValue: function (v) {
                    return v + " ₽";
                }
                valueFromText: function (t) {
                    if (t.endsWith(" ₽")) {
                        return parseInt(t.substring(0, t.length - 1));
                    }
                    return parseInt(t);
                }
                onValueChanged: {
                    root.priceChanged(Number(value));
                }
            }
        }
    }
}

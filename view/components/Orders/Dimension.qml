import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

RowLayout {
    id: root

    property alias title: titleLabel.text
    property alias value: spin.value

    signal dimensionValueChanged(real value)

    Label {
        id: titleLabel
        text: qsTr("width")
    }
    Item {
        Layout.fillWidth: true
    }
    SpinBox {
        id: spin
        from: 1
        to: 10000
        stepSize: 1
        editable: true
        value: 10

        textFromValue: function (v) {
            return v + " sm";
        }
        valueFromText: function (t) {
            if (t.endsWith(" sm")) {
                return parseInt(t.substring(0, t.length - 3));
            } else if (t.endsWith("sm")) {
                return parseInt(t.substring(0, t.length - 2));
            } else if (t.endsWith(" mm")) {
                return parseInt(t.substring(0, t.length - 3)) / 100;
            } else if (t.endsWith("mm")) {
                return parseInt(t.substring(0, t.length - 2)) / 100;
            }
            return parseInt(t);
        }
        onValueChanged: {
            root.dimensionValueChanged(value);
        }
    }
}

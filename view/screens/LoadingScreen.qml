import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import org.kde.kirigami as Kirigami

Kirigami.Page {
    id: root

    signal switched(int index)

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        anchors.topMargin: 20
        Layout.fillHeight: true
        spacing: 10
        ActionButton {
            text: qsTr("Profile")
            Layout.fillWidth: true
            onClicked: {
                root.switched(2);
            }
        }
        ActionButton {
            text: qsTr("Register way")
            Layout.fillWidth: true
            onClicked: {
                root.switched(3);
            }
        }
        ActionButton {
            text: qsTr("find")
            Layout.fillWidth: true
            onClicked: {
                root.switched(4);
            }
        }
    }
}

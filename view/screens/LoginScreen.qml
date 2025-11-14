// Main.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Item {
    id: root
    anchors.fill: parent
    visible: true
    Column {
        anchors.fill: parent
        spacing: 10
        TextField {
            placeholderText: "email"
            width: parent.width * 0.8
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            placeholderText: "Password"
            width: parent.width * 0.8
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Button {
            text: "Login"
            width: parent.width * 0.8
            palette.buttonText: theme.background
            height: 40
            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                color: theme.primary
                radius: 5
            }
        }
    }
}

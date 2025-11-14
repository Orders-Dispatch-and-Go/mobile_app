import QtQuick

Window {
    width: 400
    height: 480
    visible: true
    title: qsTr("Hello World")
    LoginScreen {
        id: loginScreen
        anchors.fill: parent
    }
}

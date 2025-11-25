import QtQuick
import QtQuick.Layouts

Window {
    width: 400
    height: 480
    visible: true
    title: qsTr("Hello World")
    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: 0
        LoginScreen {
            id: loginScreen
            anchors.fill: parent
        }
        Rectangle {
            id: mainScreen
            color: "red"
            anchors.fill: parent
        }
    }

    Connections {
        target: backend
        onScreen_switched: screen_id => {
            stackLayout.currentIndex = screen_id;
        }
    }
}

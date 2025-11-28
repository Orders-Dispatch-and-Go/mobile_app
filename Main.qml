import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    width: 400
    height: 480
    visible: true
    title: qsTr("Hello World")

    Component.onCompleted: {
        pageStack.clear();
        pageStack.push(loginComponent);
    }

    Component {
        id: loginComponent
        LoginScreen {}
    }

    Component {
        id: mainComponent
        MainScreen {}
    }

    Connections {
        target: backend
        onScreen_switched: screen_id => {
            switch (screen_id) {
            case 0:
                pageStack.clear();
                pageStack.push(loginComponent);
                break;
            case 1:
                pageStack.clear();
                pageStack.push(mainComponent);
                break;
            }
        }
    }
}

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    id: root
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
        MainScreen {
            onSwitched: id => {
                root.switchScreen(id);
            }
        }
    }

    Component {
        id: profileComponent
        ProfileScreen {}
    }

    Component {
        id: stockScreen
        StockScreen {}
    }

    Component {
        id: wayScreen
        WayScreen {}
    }

    Connections {
        target: backend
        onScreen_switched: screen_id => {
            root.switchScreen(screen_id);
        }
    }
    function switchScreen(screenId) {
        switch (screenId) {
        case 0:
            pageStack.clear();
            pageStack.push(loginComponent);
            break;
        case 1:
            pageStack.clear();
            pageStack.push(mainComponent);
            break;
        case 2:
            pageStack.clear();
            pageStack.push(profileComponent);
            break;
        case 3:
            pageStack.clear();
            pageStack.push(wayScreen);
            break;
        case 4:
            pageStack.clear();
            pageStack.push(stockScreen);
            break;
        }
    }
}

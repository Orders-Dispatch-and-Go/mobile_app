import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import org.kde.kirigami 2.19 as Kirigami

Kirigami.ApplicationWindow {
    id: root
    title: "Actions Demo"
    globalDrawer: Kirigami.GlobalDrawer {
        title: "Demo"
        titleIcon: "applications-graphics"
        actions: [
            Kirigami.Action {
                text: qsTr("Get order")
                onTriggered: root.switchScreen(3)
            },
            Kirigami.Action {
                text: "Profile"
                onTriggered: root.switchScreen(2)
            },
            Kirigami.Action {
                text: "Logout"
                onTriggered: backend.logout()
            }
        ]
    }

    Component.onCompleted: {
        pageStack.clear();
        pageStack.push(loginComponent);
    }

    Component {
        id: loginComponent
        LoginScreen {}
    }

    Component {
        id: loadingComponent
        LoadingScreen {
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
        console.log("switchScreen called with id:", screenId);
        const id = Number(screenId);
        console.log(id, screens.get_order);
        switch (id) {
        case Number(screens.login):
            pageStack.clear();
            pageStack.push(loginComponent);
            break;
        case Number(screens.loading):
            pageStack.clear();
            pageStack.push(loadingComponent);
            break;
        case Number(screens.profile):
            pageStack.clear();
            pageStack.push(profileComponent);
            break;
        case Number(screens.get_order):
            console.log("switch");
            pageStack.clear();
            pageStack.push(wayScreen);
            break;
        }
    }
}

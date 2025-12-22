import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import org.kde.kirigami 2.19 as Kirigami

Kirigami.ApplicationWindow {
    id: root
    width: 400
    height: 600
    minimumHeight: 400
    title: "GruzoWiki"
    globalDrawer: Kirigami.GlobalDrawer {
        title: "GruzoWiki"
        actions: [
            Kirigami.Action {
                text: "Profile"
                onTriggered: backend.switchScreen(screens.profile)
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
        id: profileComponent
        ProfileScreen {}
    }
    Component {
        id: startRouteScreen
        StartRouteScreen {}
    }
    Component {
        id: getOrdersScreen
        GetOrdersScreen {}
    }
    Component {
        id: finishRouteScreen
        FinishRouteScreen {}
    }
    Component {
        id: currentRouteScreen
        RouteScreen {}
    }

    Connections {
        target: backend
        onScreenSwitched: {
            root.switchScreen();
        }
    }
    function switchScreen() {
        const screenId = backend.screenId;
        console.log("screen id = ", screenId);
        const id = Number(screenId);
        switch (id) {
        case Number(screens.login):
            pageStack.clear();
            pageStack.push(loginComponent);
            break;
        case Number(screens.profile):
            pageStack.clear();
            pageStack.push(profileComponent);
            break;
        case Number(screens.startRoute):
            pageStack.clear();
            pageStack.push(startRouteScreen);
            break;
        case Number(screens.finishRoute):
            pageStack.clear();
            pageStack.push(finishRouteScreen);
            break;
        case Number(screens.getOrders):
            pageStack.clear();
            pageStack.push(getOrdersScreen);
            break;
        case Number(screens.currentRoute):
            pageStack.clear();
            pageStack.push(currentRouteScreen);
            break;
        default:
            pageStack.clear();
            pageStack.push(loginComponent);
            break;
        }
    }
}

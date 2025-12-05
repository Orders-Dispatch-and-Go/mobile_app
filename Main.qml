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
                text: qsTr("TEST Start new route")
                onTriggered: root.switchScreen(screens.startRoute)
            },
            Kirigami.Action {
                text: qsTr("TEST get order")
                onTriggered: root.switchScreen(screens.getOrders)
            },
            Kirigami.Action {
                text: qsTr("TEST current route")
                onTriggered: root.switchScreen(screens.currentRoute)
            },
            Kirigami.Action {
                text: qsTr("TEST finishOrder")
                onTriggered: root.switchScreen(screens.finishOrder)
            },
            Kirigami.Action {
                text: qsTr("TEST finish route screen")
                onTriggered: root.switchScreen(screens.finishRoute)
            },
            Kirigami.Action {
                text: "Profile"
                onTriggered: root.switchScreen(screens.profile)
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
        id: finishOrderScreen
        FinishOrderScreen {}
    }
    Component {
        id: currentRouteScreen
        RouteScreen {}
    }

    Connections {
        target: backend
        onScreen_switched: screen_id => {
            root.switchScreen(screen_id);
        }
    }
    function switchScreen(screenId) {
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
        case Number(screens.finishOrder):
            pageStack.clear();
            pageStack.push(finishOrderScreen);
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

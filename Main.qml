import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import org.kde.kirigami 2.19 as Kirigami

Kirigami.ApplicationWindow {
    id: root
    width: 240
    height: 400
    title: "Actions Demo"
    globalDrawer: Kirigami.GlobalDrawer {
        title: "Demo"
        titleIcon: "applications-graphics"
        actions: [
            Kirigami.Action {
                text: qsTr("Start new route")
                onTriggered: root.switchScreen(screens.startRoute)
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
        id: ordersScreen
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
        case Number(screens.getOrders):
            pageStack.clear();
            pageStack.push(ordersScreen);
            break;
        case Number(screens.finishOrder):
            pageStack.clear();
            pageStack.push(finishOrderScreen);
            break;
        case Number(screens.finishRoute):
            pageStack.clear();
            pageStack.push(finishRouteScreen);
            break;
        default:
            pageStack.clear();
            pageStack.push(loginComponent);
            break;
        }
    }
}

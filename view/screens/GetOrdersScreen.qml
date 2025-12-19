import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Kirigami.Page {
    id: root
    title: qsTr("Choose orders for trip")

    property var orders: backend.relevantOrders
    property var gotOrders: backend.userOrders

    Component.onCompleted: {
        console.log(orders);
        console.log(gotOrders);
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Kirigami.Units.smallSpacing

        ScrollView {
            id: scrollView
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true

            ScrollBar.vertical.policy: ScrollBar.AlwaysOff
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

            Item {
                width: scrollView.width
                implicitHeight: contentColumn.implicitHeight

                ColumnLayout {
                    id: contentColumn
                    width: parent.width
                    spacing: Kirigami.Units.largeSpacing

                    Repeater {
                        model: root.gotOrders
                        delegate: Kirigami.Card {
                            header: Kirigami.Heading {
                                text: "#" + ("" + modelData.uuid).split("-")[1]
                            }
                        }
                    }

                    Repeater {
                        model: root.orders
                        delegate: OrderCard {
                            dto: modelData
                            Layout.fillWidth: true
                            onAccepted: () => {
                                console.log(modelData.index);
                                backend.acceptRelevant(modelData.index);
                            }
                            onRejected: () => {
                                console.log(modelData.index);
                                backend.rejectRelevant(modelData.index);
                            }
                        }
                    }
                }

                ColumnLayout {
                    anchors.centerIn: parent
                    anchors.fill: parent
                    visible: root.orders.length === 0 && root.gotOrders.length === 0
                    Text {
                        text: qsTr("No orders found")
                    }
                    Button {
                        text: qsTr("back")
                        onClicked: {
                            backend.switchScreen(screens.pStartRoute);
                        }
                    }
                }
            }
        }

        Button {
            text: qsTr("Start")
            Layout.fillWidth: true
            enabled: root.gotOrders.length > 0
            onClicked: {}
        }
    }
}

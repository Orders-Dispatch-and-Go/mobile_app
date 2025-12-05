import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Kirigami.Page {
    id: root
    title: qsTr("Choose orders for trip")

    property var dto: {
        id: 42;
        description: "Sample order description";
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

            ColumnLayout {
                width: scrollView.width
                spacing: Kirigami.Units.largeSpacing

                Order {
                    id: order1
                    dto: root.dto
                    Layout.fillWidth: true
                }

                Order {
                    id: order2
                    dto: root.dto
                    Layout.fillWidth: true
                }
            }
        }

        Button {
            text: qsTr("Start")
            Layout.fillWidth: true

            onClicked: {
                backend.startTrip();
            }
        }
    }
}

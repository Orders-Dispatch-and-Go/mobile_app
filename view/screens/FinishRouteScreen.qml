import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Kirigami.Page {
    title: qsTr("Route Finished")
    ColumnLayout {
        anchors.fill: parent
        Kirigami.Heading {
            text: qsTr("You can start a new route")
            level: 1
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Kirigami.Icon {
                anchors.fill: parent
                anchors.margins: Kirigami.Units.largeSpacing * 5
                source: "task-complete"
                width: Kirigami.Units.iconSizes.large
                height: width
            }
        }
        Button {
            text: qsTr("Start New Route")
            Layout.fillWidth: true
            onClicked: {
                backend.switchScreen(screens.pStartRoute);
            }
        }
    }
}

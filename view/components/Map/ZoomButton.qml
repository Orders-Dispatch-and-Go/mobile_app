import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

Rectangle {
    id: zoomButton

    property alias text: title.text
    property var zoomAction: () => {}

    color: Kirigami.Theme.backgroundColor
    width: 32
    height: 32
    radius: 16
    z: 1000

    Text {
        id: title
        text: "+"
        color: "white"
        font.pixelSize: 24
        anchors.centerIn: parent
    }
    MouseArea {
        id: area
        anchors.fill: parent
        onClicked: zoomButton.zoomAction()
    }
}

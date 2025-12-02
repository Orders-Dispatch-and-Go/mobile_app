import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Rectangle {
    id: root
    radius: 10

    color: Kirigami.Theme.backgroundColor
    border.color: Kirigami.Theme.activeBackgroundColor
    border.width: 3
    Text {
        text: "Order"
        color: Kirigami.Theme.activeTextColor
        font.bold: true
        anchors.centerIn: parent
    }
}

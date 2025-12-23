import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

Rectangle {
    id: root
    property var point

    color: Kirigami.Theme.backgroundColor
    border.color: Kirigami.Theme.disabledTextColor
    border.width: 1
    radius: Kirigami.Units.cornerRadius

    RowLayout {
        spacing: Kirigami.Units.smallSpacing
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing
        Rectangle {
            radius: 5
            width: 10
            height: 10
            color: "lightblue"
        }
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                text: point.address
                color: Kirigami.Theme.textColor
                wrapMode: Text.WordWrap
                elide: Text.ElideNone
                Layout.fillWidth: true
            }
            Text {
                Layout.fillWidth: true
                text: "(" + point.lat + "," + point.lon + ")"
                color: Kirigami.Theme.textColor
            }
        }
    }
}

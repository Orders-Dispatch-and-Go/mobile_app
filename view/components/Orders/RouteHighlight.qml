import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

Kirigami.AbstractCard {
    id: root

    property var point

    height: 100
    contentItem: RowLayout {
        spacing: 10
        Rectangle {
            radius: 5
            width: 10
            height: 10
            color: "lightblue"
        }
        Text {
            text: point.address
            color: Kirigami.Theme.textColor
        }
        Item {
            Layout.fillWidth: true
        }
        Text {
            text: "(" + point.lat + "," + point.lon + ")"
            color: Kirigami.Theme.textColor
        }
    }
}

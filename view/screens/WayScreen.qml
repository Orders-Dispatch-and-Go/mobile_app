import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.Page {
    id: root
    title: qsTr("Get orders")

    Order {
        width: parent.width
        height: parent.height
    }
}

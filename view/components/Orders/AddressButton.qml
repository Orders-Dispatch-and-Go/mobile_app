import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Button {
    id: root

    height: 30

    text: "address"

    property string address: "123 Main St"
    property real latitude: 40.7128
    property real longitude: -74.0060
}

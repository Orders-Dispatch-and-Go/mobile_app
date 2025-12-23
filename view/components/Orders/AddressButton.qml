import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Button {
    id: root
    readonly property string title: qsTr("Нажмите, чтобы выбрать начальную и конечную точки")

    property int dialogWidth: root.parent.width
    property int dialogHeight: root.parent.height

    property bool ready: false
    property real beginLat: 0
    property real beginLon: 0
    property real endLat: 0
    property real endLon: 0

    property bool coordsAccepted: false

    onClicked: dialog.open()

    background: Rectangle {
        // скругление — выглядит аккуратно с Kirigami-стилем
        radius: 8
        // цвет меняется в зависимости от ready
        color: root.ready ? Kirigami.Theme.highlightColor        // или Kirigami.Theme.accentColor
        : Kirigami.Theme.negativeBackgroundColor
        border.color: root.pressed ? Kirigami.Theme.highlightColor : "transparent"
        border.width: root.pressed ? 1 : 0
    }
    contentItem: Text {
        text: root.ready ? root.stringify() : title
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 14
        color: root.ready ? Kirigami.Theme.textColor : Kirigami.Theme.negativeTextColor
        elide: Text.ElideRight
    }

    RouteDialog {
        id: dialog
        implicitWidth: root.dialogWidth
        implicitHeight: root.dialogHeight
        onAccepted: {
            root.ready = true;
            root.beginLat = dialog.startCoord.latitude;
            root.beginLon = dialog.startCoord.longitude;
            root.endLat = dialog.finishCoord.latitude;
            root.endLon = dialog.finishCoord.longitude;
            root.coordsAccepted = true;
        }
        onRejected: {
            root.ready = false;
        }
    }
    function stringify() {
        var begin = "(" + root.beginLat.toFixed(3) + ", " + root.beginLon.toFixed(3) + ")";
        var end = "(" + root.endLat.toFixed(3) + ", " + root.endLon.toFixed(3) + ")";
        return begin + " -> " + end;
    }
}

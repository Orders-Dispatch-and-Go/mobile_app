import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15
import QtLocation 6.5
import QtPositioning 6.5
import org.kde.kirigami 2.20 as Kirigami

import untitled

Kirigami.Dialog {
    id: root
    modal: true
    title: "Выбор точки"

    standardButtons: Kirigami.Dialog.Ok

    property var dto

    contentItem: Order {
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing
        dto: root.dto
    }
}

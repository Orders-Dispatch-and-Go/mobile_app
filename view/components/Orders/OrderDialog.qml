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
    title: "Завершить заказ"

    property int index: -1
    property var dto

    signal commit(int i)
    signal cancel(int i)

    contentItem: Order {
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing * 3
        anchors.topMargin: Kirigami.Units.largeSpacing * 5
        dto: root.dto
    }

    customFooterActions: [
        Kirigami.Action {
            text: "Отменить"
            onTriggered: {
                root.close();
                root.cancel(root.index);
            }
        },
        Kirigami.Action {
            text: "Закончить"
            onTriggered: {
                root.close();
                root.commit(root.index);
            }
        }
    ]
}

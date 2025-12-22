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

    signal complete(int i)
    signal cancel(int i)

    contentItem: ColumnLayout {
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing * 3
        anchors.topMargin: Kirigami.Units.largeSpacing * 5
        spacing: Kirigami.Units.largeSpacing
        Kirigami.Heading {
            text: "#" + ("" + dto.id).split("-")[1]
        }
        Order {
            dto: root.dto ? {
                "price": root.dto.price,
                "start": {
                    "address": root.dto.fromStation.address,
                    "coords": root.dto.fromStation.coords
                },
                "finish": {
                    "address": root.dto.toStation.address,
                    "coords": root.dto.toStation.coords
                }
            } : null
        }
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
                root.complete(root.index);
            }
        }
    ]
}

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls 2.15
import org.kde.kirigami as Kirigami

import untitled

Kirigami.ScrollablePage {
    id: root
    title: qsTr("Start new route")
    ColumnLayout {
        height: parent.height
        Filter {
            id: order
            Layout.fillWidth: true
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Button {
            Layout.fillWidth: true
            text: "find orders"
            onClicked: {
                if (!order.coordsAccepted) {
                    return;
                }
                const w = order.useSize ? Number(order.dimWidth) : -1;
                const h = order.useSize ? Number(order.dimHeight) : -1;
                const d = order.useSize ? Number(order.dimDepth) : -1;

                const price = order.usePrice ? Number(order.price) : -1;

                const date = order.useRouteDate ? order.routeDate : "";
                console.log(w, h, d);
                console.log(price, date);

                backend.setupFilter(w, h, d, price, date);
                backend.startTrip(order.beginLat, order.beginLon, order.endLat, order.endLon);
            }
        }
    }
}

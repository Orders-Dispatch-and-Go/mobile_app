import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: root

    property alias useSize: sizes.used
    property alias dimHeight: sizes.dimHeight
    property alias dimWidth: sizes.dimWidth
    property alias dimDepth: sizes.dimDepth

    property alias usePrice: minPrice.used
    property alias price: minPrice.value

    property alias useRouteDate: routeDate.used
    property alias routeDate: routeDate.value

    property alias beginLat: wayButton.beginLat
    property alias beginLon: wayButton.beginLon
    property alias endLat: wayButton.endLat
    property alias endLon: wayButton.endLon

    property alias coordsAccepted: wayButton.coordsAccepted

    AddressButton {
        id: wayButton
        dialogWidth: root.parent.width
        dialogHeight: root.parent.height
        Layout.fillWidth: true
    }
    Sizes {
        id: sizes
        Layout.fillWidth: true
    }
    MinPrice {
        id: minPrice
        Layout.fillWidth: true
    }
    RouteDate {
        id: routeDate
        Layout.fillWidth: true
    }
}

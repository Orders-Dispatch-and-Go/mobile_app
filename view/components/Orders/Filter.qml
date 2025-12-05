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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: root

    property alias beginAddress: beginAddressButton.address
    property alias beginLat: beginAddressButton.latitude
    property alias beginLon: beginAddressButton.longitude
    property alias endAddress: endAddressButton.address
    property alias endLat: endAddressButton.latitude
    property alias endLon: endAddressButton.longitude

    property alias useSize: sizes.used
    property alias dimHeight: sizes.dimHeight
    property alias dimWidth: sizes.dimWidth
    property alias dimDepth: sizes.dimDepth

    property alias usePrice: minPrice.used
    property alias price: minPrice.value

    property alias useRouteDate: routeDate.used
    property alias routeDate: routeDate.value

    AddressButton {
        id: beginAddressButton
        Layout.fillWidth: true
    }
    AddressButton {
        id: endAddressButton
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

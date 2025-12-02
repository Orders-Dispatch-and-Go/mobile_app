import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    id: root
    Sizes {
        id: sizes
        Layout.fillWidth: true
    }
    MinPrice {
        id: minPrice
        Layout.fillWidth: true
    }
}

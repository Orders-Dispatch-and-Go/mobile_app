import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.20 as Kirigami

Kirigami.ScrollablePage {
    id: page
    title: qsTr("Профиль")

    padding: Kirigami.Units.largeSpacing

    ColumnLayout {
        anchors.fill: parent
        spacing: Kirigami.Units.smallSpacing

        // Универсальный компонент для строки данных
        Component {
            id: rowDelegate
            RowLayout {
                spacing: Kirigami.Units.smallSpacing
                width: parent.width

                Controls.Label {
                    text: model.label
                    Layout.preferredWidth: parent.width * 0.4
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                    color: Kirigami.Theme.textColor
                }
                Item {
                    Layout.fillWidth: true
                }

                RowLayout {
                    spacing: Kirigami.Units.smallSpacing
                    Controls.Label {
                        text: model.value
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignLeft
                        color: Kirigami.Theme.textColor
                    }

                    Controls.ToolButton {
                        visible: model.editable
                        icon.name: "document-edit"
                        onClicked: {}
                    }
                }

                Layout.fillWidth: true
            }
        }

        // Список данных
        ListView {
            id: list
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: Kirigami.Units.smallSpacing

            model: ListModel {
                ListElement {
                    name: "email"
                    editable: false
                    label: qsTr("Email")
                    value: backend.userEmail
                }
                ListElement {
                    name: "surname"
                    editable: true
                    label: qsTr("Фамилия")
                    value: backend.userSurname
                }
                ListElement {
                    name: "name"
                    editable: true
                    label: qsTr("Имя")
                    value: backend.userName
                }
                ListElement {
                    name: "patronymic"
                    editable: true
                    label: qsTr("Отчество")
                    value: backend.userPatronymic
                }
                ListElement {
                    label: qsTr("Серия паспорта")
                    editable: true
                    value: backend.userSeria
                }
                ListElement {
                    label: qsTr("Номер паспорта")
                    editable: true
                    value: backend.userNumber
                }
                ListElement {
                    label: "Текущий адрес"
                    editable: true
                    value: backend.userAddress
                }
            }

            delegate: rowDelegate
        }
    }
}

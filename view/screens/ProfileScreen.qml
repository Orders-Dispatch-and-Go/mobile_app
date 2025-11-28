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

        // ---- Email ----
        RowLayout {
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Controls.Label {
                text: qsTr("Email")
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
            Item {
                Layout.fillWidth: true
            }

            Controls.Label {
                text: backend.userEmail
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }

            Controls.ToolButton {
                visible: false
            }
        }

        // ---- Фамилия ----
        RowLayout {
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Controls.Label {
                text: qsTr("Фамилия")
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Label {
                text: backend.userSurname
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }

            Controls.ToolButton {
                visible: true
                icon.name: "document-edit"
            }
        }

        // ---- Имя ----
        RowLayout {
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Controls.Label {
                text: qsTr("Имя")
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Label {
                text: backend.userName
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }

            Controls.ToolButton {
                visible: true
                icon.name: "document-edit"
            }
        }

        // ---- Отчество ----
        RowLayout {
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Controls.Label {
                text: qsTr("Отчество")
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Label {
                text: backend.userPatronymic
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }

            Controls.ToolButton {
                visible: true
                icon.name: "document-edit"
            }
        }

        // ---- Серия паспорта ----
        RowLayout {
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Controls.Label {
                text: qsTr("Серия паспорта")
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Label {
                text: backend.userSeria
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }

            Controls.ToolButton {
                visible: true
                icon.name: "document-edit"
            }
        }

        // ---- Номер паспорта ----
        RowLayout {
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Controls.Label {
                text: qsTr("Номер паспорта")
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Label {
                text: backend.userNumber
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }

            Controls.ToolButton {
                visible: true
                icon.name: "document-edit"
            }
        }

        // ---- Текущий адрес ----
        RowLayout {
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Controls.Label {
                text: qsTr("Текущий адрес")
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Label {
                text: backend.userAddress
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }

            Controls.ToolButton {
                visible: true
                icon.name: "document-edit"
            }
        }
    }
}

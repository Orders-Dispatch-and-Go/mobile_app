import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as Controls
import org.kde.kirigami 2.20 as Kirigami

Kirigami.ScrollablePage {
    id: page
    title: qsTr("Профиль")
    padding: Kirigami.Units.largeSpacing

    // Состояние редактирования
    property bool editing: false
    property string editingField: ""
    property string editingOriginalValue: ""
    property string editingValue: ""

    ColumnLayout {
        anchors.fill: parent
        spacing: Kirigami.Units.smallSpacing

        // ======== EMAIL (НЕ РЕДАКТИРУЕТСЯ) ===========
        RowLayout {
            Layout.fillWidth: true
            Controls.Label {
                text: qsTr("Email")
            }
            Item {
                Layout.fillWidth: true
            }
            Controls.Label {
                text: backend.userEmail
            }
            Controls.ToolButton {
                visible: false
            }
        }

        // ======== ФАМИЛИЯ ===========
        RowLayout {
            Layout.fillWidth: true

            Controls.Label {
                text: qsTr("Фамилия")
            }
            Item {
                Layout.fillWidth: true
            }

            // Если это редактируемое поле
            Controls.TextField {
                visible: editing && editingField === "surname"
                text: editingValue
                onTextChanged: editingValue = text
                Layout.preferredWidth: parent.width * 0.4
            }

            Controls.Label {
                visible: !(editing && editingField === "surname")
                text: backend.userSurname
            }

            Controls.ToolButton {
                icon.name: "document-edit"
                visible: !editing
                onClicked: {
                    editing = true;
                    editingField = "surname";
                    editingValue = backend.userSurname;
                }
            }
        }

        // ======== ИМЯ ===========
        RowLayout {
            Layout.fillWidth: true

            Controls.Label {
                text: qsTr("Имя")
            }
            Item {
                Layout.fillWidth: true
            }

            Controls.TextField {
                visible: editing && editingField === "name"
                text: editingValue
                onTextChanged: editingValue = text
                Layout.preferredWidth: parent.width * 0.4
            }

            Controls.Label {
                visible: !(editing && editingField === "name")
                text: backend.userName
            }

            Controls.ToolButton {
                icon.name: "document-edit"
                visible: !editing
                onClicked: {
                    editing = true;
                    editingField = "name";
                    editingValue = backend.userName;
                }
            }
        }

        // ======== ОТЧЕСТВО ===========
        RowLayout {
            Layout.fillWidth: true

            Controls.Label {
                text: qsTr("Отчество")
            }
            Item {
                Layout.fillWidth: true
            }

            Controls.TextField {
                visible: editing && editingField === "patronymic"
                text: editingValue
                onTextChanged: editingValue = text
                Layout.preferredWidth: parent.width * 0.4
            }

            Controls.Label {
                visible: !(editing && editingField === "patronymic")
                text: backend.userPatronymic
            }

            Controls.ToolButton {
                icon.name: "document-edit"
                visible: !editing
                onClicked: {
                    editing = true;
                    editingField = "patronymic";
                    editingValue = backend.userPatronymic;
                }
            }
        }

        // ======== СЕРИЯ ПАСПОРТА ===========
        RowLayout {
            Layout.fillWidth: true

            Controls.Label {
                text: qsTr("Серия паспорта")
            }
            Item {
                Layout.fillWidth: true
            }

            Controls.TextField {
                visible: editing && editingField === "seria"
                text: editingValue
                inputMethodHints: Qt.ImhDigitsOnly
                onTextChanged: editingValue = text
                Layout.preferredWidth: parent.width * 0.4
            }

            Controls.Label {
                visible: !(editing && editingField === "seria")
                text: backend.userSeria
            }

            Controls.ToolButton {
                icon.name: "document-edit"
                visible: !editing
                onClicked: {
                    editing = true;
                    editingField = "seria";
                    editingValue = backend.userSeria;
                }
            }
        }

        // ======== НОМЕР ПАСПОРТА ===========
        RowLayout {
            Layout.fillWidth: true

            Controls.Label {
                text: qsTr("Номер паспорта")
            }
            Item {
                Layout.fillWidth: true
            }

            Controls.TextField {
                visible: editing && editingField === "number"
                text: editingValue
                inputMethodHints: Qt.ImhDigitsOnly
                onTextChanged: editingValue = text
                Layout.preferredWidth: parent.width * 0.4
            }

            Controls.Label {
                visible: !(editing && editingField === "number")
                text: backend.userNumber
            }

            Controls.ToolButton {
                icon.name: "document-edit"
                visible: !editing
                onClicked: {
                    editing = true;
                    editingField = "number";
                    editingValue = backend.userNumber;
                }
            }
        }

        // ======== АДРЕС ===========
        RowLayout {
            Layout.fillWidth: true

            Controls.Label {
                text: qsTr("Текущий адрес")
            }
            Item {
                Layout.fillWidth: true
            }

            Controls.TextField {
                visible: editing && editingField === "address"
                text: editingValue
                onTextChanged: editingValue = text
                Layout.preferredWidth: parent.width * 0.4
            }

            Controls.Label {
                visible: !(editing && editingField === "address")
                text: backend.userAddress
            }

            Controls.ToolButton {
                icon.name: "document-edit"
                visible: !editing
                onClicked: {
                    editing = true;
                    editingField = "address";
                    editingValue = backend.userAddress;
                }
            }
        }
    }

    footer: footerItem
    ColumnLayout {
        id: footerItem
        width: parent.width
        height: Kirigami.Units.gridUnit * 3

        RowLayout {
            spacing: Kirigami.Units.largeSpacing
            height: page.editing ? Kirigami.Units.gridUnit * 3 : 0
            visible: page.editing
            Layout.fillWidth: true

            Controls.Button {
                text: qsTr("Отмена")
                Layout.fillWidth: true
                onClicked: {
                    page.editing = false;
                    page.editingField = "";
                    page.editingValue = "";
                }
            }

            Controls.Button {
                text: qsTr("OK")
                Layout.fillWidth: true
                onClicked: page.saveChanges()
            }
        }
        RowLayout {
            Layout.fillWidth: true
            visible: !page.editing
            height: page.editing ? 0 : Kirigami.Units.gridUnit * 3

            Controls.Button {
                text: qsTr("Назад")
                Layout.fillWidth: true
                onClicked: {
                    backend.switch_screen(1);
                }
            }

            Controls.Button {
                text: qsTr("Выход")
                Layout.fillWidth: true
                onClicked: backend.logout()
            }
        }
    }
    function saveChanges() {
        switch (page.editingField) {
        case "surname":
            backend.userSurname = page.editingValue;
            break;
        case "name":
            backend.userName = page.editingValue;
            break;
        case "patronymic":
            backend.userPatronymic = page.editingValue;
            break;
        case "seria":
            backend.userSeria = parseInt(page.editingValue);
            break;
        case "number":
            backend.userNumber = parseInt(page.editingValue);
            break;
        case "address":
            backend.userAddress = page.editingValue;
            break;
        }
        page.editing = false;
        page.editingField = "";
        page.editingValue = "";
    }
}
